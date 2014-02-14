#include "Vector3d.h"
#include <vector>

using namespace std;

//Enumerations
enum ObjectTypes {SPHERE, PLANE, TRIANGLE, DIRECTIONAL, SPOT, POINT};


//Ray class
class Ray
{
	public:
		Ray();
		Ray(Vector3d pos, Vector3d dir);
		Vector3d pos;
		Vector3d dir;

};

//Abstract Object Class for dynamic binding
class Object
{
	public:
		enum ObjectTypes type;
		virtual void fprintObject(FILE *fp) = 0;
};

//Derived Sphere class
class Sphere: public Object
{
	public:
		Sphere();
		Sphere(float radius, Vector3d center, Vector3d color);
		void fprintObject(FILE *fp);
		bool intersect(Ray &r, Vector3d &pos);
		float radius;
		Vector3d center;
		Vector3d color;
};

//Derived Light class
class Light: public Object
{
	public:
		Light();
		Light(Vector3d pos, Vector3d dir, Vector3d diffuseColor, Vector3d specularColor, float diffusePower, float specularPower);
		void fprintObject(FILE *fp);
		Vector3d pos;
		Vector3d dir;
		Vector3d diffuseColor;
		Vector3d specularColor;
		float diffusePower;
		float specularPower;
};


//Scene class for describing the world
class Scene
{
	public:
		Scene();
		Scene(Vector3d eye, Vector3d bgColor);
		Vector3d eye;
		vector<Object*> objects;
		vector<Object*> lights;
		Vector3d bgColor;
};


//PPM Functions
void fprintPPMHeader(FILE *fp, int width, int height);


//Raytracer functions
void Tracer(FILE *fp, Scene &scene);
Vector3d Color_At(float x, float y, Scene &scene);
Vector3d Cast_Ray(Ray &r, Scene &scene);
bool First_Hit(Ray &r, Scene &scene, Object* &obj, Vector3d &pos);
void Quadratic(float A, float B, float C, int &Nroots, float &root1, float &root2);
Vector3d Lambert(Sphere* obj, Vector3d pos, Scene &scene);
float saturate(float x);


