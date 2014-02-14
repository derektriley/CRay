#include "rtlib.h"
#include <math.h>

/* Ray class */
Ray::Ray()
{
	this->pos.x = 0.0f;
	this->pos.y = 0.0f;
	this->pos.z = 0.0f;
	this->dir.x = 0.0f;
	this->dir.y = 0.0f;
	this->dir.z = 0.0f;
}

Ray::Ray(Vector3d pos, Vector3d dir)
{
	this->pos = pos;
	this->dir = dir;
}
/*************/

/* Sphere Class Functions */
Sphere::Sphere()
{
	this->type = SPHERE;
	this->radius = 0.0f;
	this->color.x = 0.0f;
	this->color.y = 0.0f;
	this->color.z = 0.0f;
	this->center.x = 0.0f;
	this->center.y = 0.0f;
	this->center.z = 0.0f;
}

Sphere::Sphere(float radius, Vector3d center, Vector3d color)
{
	this->type = SPHERE;
	this->radius = radius;
	this->color = color;
	this->center = center;
}

bool Sphere::intersect(Ray &r, Vector3d &pos)
{
	float A, B, C;
	float root1, root2;
	int Nroots;
	Vector3d Object_Ray = r.pos - this->center;
	A = r.dir * r.dir;
	B = 2.0f * (Object_Ray * r.dir);
	C = (Object_Ray * Object_Ray) - (this->radius * this->radius); 
	Quadratic(A, B, C, Nroots, root1, root2);
	if (Nroots == 0) {
		return false;
	}
	else if (root1 > 0.0f) {
		pos = r.dir;
		pos = pos * root1;
		pos = r.pos + pos;
		return true;
	}
	else if (root2 > 0.0f) {
		pos = r.dir;
		pos = pos * root2;
		pos = r.pos + pos;
		return true;
	}
	else {
		return false;
	}
}

void Sphere::fprintObject(FILE *fp)
{
	fprintf(fp, "Type:%d\nRadius:%f\nCenter:%f %f %f\nColor:%f %f %f\n", this->type, this->radius, this->center.x, this->center.y, this->center.z, this->color.x, this->color.y, this->color.z);
}

/*************************/


/* Scene Class Functions */
Scene::Scene()
{
	this->eye.x = 0.0f;
	this->eye.y = 0.0f;
	this->eye.z = 100.0f;
	this->bgColor.x = 0.0f;
	this->bgColor.y = 0.635f;
	this->bgColor.z = 0.909f;
}

Scene::Scene(Vector3d eye, Vector3d bgColor)
{
	this->eye.x = eye.x;
	this->eye.y = eye.y;
	this->eye.z = eye.z;
	this->bgColor.x = bgColor.x;
	this->bgColor.y = bgColor.y;
	this->bgColor.z = bgColor.z;
}
/*************************/


/* Light Class Functions */
Light::Light()
{
	this->diffuseColor.x = 0.0f;
	this->diffuseColor.y = 0.0f;
	this->diffuseColor.z = 0.0f;
	this->pos.x = 0.0f;
	this->pos.y = 0.0f;
	this->pos.z = 0.0f;
	this->dir.x = 0.0f;
	this->dir.y = 0.0f;
	this->dir.z = 0.0f;
}

Light::Light(Vector3d pos, Vector3d dir, Vector3d diffuseColor, Vector3d specularColor, float diffusePower, float specularPower)
{
	this->pos = pos;
	this->dir = dir;
	this->diffuseColor = diffuseColor;
	this->specularColor = specularColor;
	this->diffusePower = diffusePower;
	this->specularPower = specularPower;
}


void Light::fprintObject(FILE *fp)
{
	fprintf(fp, "Type:%d\nPos:%f %f %f\nColor:%f %f %f\n", this->type, this->pos.x, this->pos.y, this->pos.z, this->diffuseColor.x, this->diffuseColor.y, this->diffuseColor.z);
}
/*************************/


//PPM Functions
void fprintPPMHeader(FILE *fp, int width, int height)
{
	fprintf(fp, "P3\n%d %d\n255\n", width, height);
}

//Raytracer functions
void Tracer(FILE *fp, Scene &scene)
{
	fprintPPMHeader(fp, 1920, 1080);
	float x, y;
	float inc = 0.0416f;
	Vector3d color(0.785f, 0.235f, 0.455f);
	//Let's new a buffer the size of the screen for paralellism
	Vector3d **buffer;
	
	//Allocate memory
	buffer = new Vector3d*[1080];
	for (int i = 0; i < 1080; i++)
		buffer[i] = new Vector3d[1920];	

	y = 22.5f;
	for (int i = 0; i < 1080; i++)
	{
		x = -40.0f;
		for (int j = 0; j < 1920; j++)
		{
			//Get the color at this pixel
			//color = Color_At(x, y, scene);
			buffer[i][j] = Color_At(x, y, scene);
			x += inc;
		}
		fprintf(fp, "\n");
		y -= inc;
	}

	
	//Print all Vector3d's in the buffer to the fp
	for (int i = 0; i < 1080; i++)
	{
		for(int j = 0; j < 1920; j++)
		{
			buffer[i][j].fprintVector3d255(fp);
		}
	}

	//De-Allocate memory to prevent memory leak
	for (int i = 0; i < 1080; i++)
		delete [] buffer[i];
	delete [] buffer;
}


Vector3d Color_At(float x, float y, Scene &scene)
{
	Vector3d pos(x, y, 0.0f);
	Ray r;
	
	r.pos = scene.eye;
	r.dir = pos - scene.eye;
	
	return Cast_Ray(r, scene);
}

Vector3d Cast_Ray(Ray &r, Scene &scene)
{
	Object* obj = NULL;
	Vector3d color; //Color to be returned unless bgColor
	Vector3d pos; //Position in 3d space where intersection occured

	if (First_Hit(r, scene, obj, pos))
	{
		//Compute illumination
		color = Lambert((Sphere*)obj, pos, scene);
		//color = ((Sphere*)obj)->color;
		return color;
	}
	else {
		return scene.bgColor;
	}
}

bool First_Hit(Ray &r, Scene &scene, Object* &obj, Vector3d &pos)
{
	float dist = 1.0e20;
	float tmp_dist;
	Vector3d tmp_pos;
	bool success = false;
	
	vector<Object*>::iterator v = scene.objects.begin();
	while (v != scene.objects.end())
	{	
			if ((*v)->type == SPHERE) {
				if (((Sphere*)(*v))->intersect(r, tmp_pos)) {
					//There was an intersection
					//fprintf(stderr, "Intersection!\n");
					if (tmp_dist < dist) {
						success = true;
						dist = tmp_dist;
						pos = tmp_pos;
						obj = *v;
					}
				}
			}
		v++;
	}
	if (success) {
		return true;
	}
	return false;		
}

void Quadratic(float A, float B, float C, int &Nroots, float &root1, float &root2)
{
	float Discriminant, sqrtDiscriminant;
	Discriminant = (B*B) - (4.0f*A*C);
	if (Discriminant < 0.0f) {
		Nroots = 0;
	}
	else if (Discriminant == 0.0f) {
		Nroots = 1;
		root1 = -B/(2.0f*A);
	}
	else {
		Nroots = 2;
		sqrtDiscriminant = sqrt(Discriminant);
		root1 = (-B - sqrtDiscriminant)/(2.0f*A);
		root2 = (-B + sqrtDiscriminant)/(2.0f*A);
	}
}

Vector3d Lambert(Sphere* obj, Vector3d pos, Scene &scene)
{
	Light* l = ((Light*)(scene.lights[0]));
	Vector3d lightDir = l->pos - pos;
	Vector3d normal = pos - obj->center;
	Vector3d viewDir = scene.eye - pos;
	Vector3d Diffuse;
	Vector3d Specular;
	float distance = lightDir.Mag();
	normal.Normalize();
	lightDir.Normalize();
	
	//Intensity of the diffuse light. Saturate to keep within the 0-1 range.
	float NdotL = normal * lightDir;
	float intensity = saturate(NdotL);

	return obj->color * intensity; 
	fprintf(stderr, "intensity:%f\n", intensity);

	// Calculate the diffuse light factoring in light color, power and the attenuation
	Diffuse = intensity * l->diffuseColor * l->diffusePower / distance;

	//Calculate the half vector between the light vector and the view vector.
    //This is faster than calculating the actual reflective vector.
    Vector3d H = (lightDir + viewDir);
	H.Normalize();
	
	//Intensity of the specular light
	float NdotH = normal * H;
	intensity = pow( saturate(NdotH), 15.0f); //Second param is specularHardness

	//Sum up the specular light factoring
	Specular = intensity * l->specularColor * l->specularPower / distance; 

	Diffuse.x = Diffuse.x * obj->color.x;
	Diffuse.y = Diffuse.y * obj->color.y;
	Diffuse.z = Diffuse.z * obj->color.z;
	fprintf(stderr, "%f %f %f\n", Diffuse.x, Diffuse.y, Diffuse.z);

	return Diffuse;
}

float saturate(float x) {
	if (x < 0.0f) {
		return 0.0f;
	}
	else if (x > 1.0f) {
		return 1.0f;
	}
	else {
		return x;
	}
}
