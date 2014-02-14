#include "Vector3d.h"
#include <math.h>

Vector3d::Vector3d() //Default constructor
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

Vector3d::Vector3d(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}


void Vector3d::setComps(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3d Vector3d::operator+(const Vector3d& b)
{	
	Vector3d v;
	v.setComps(this->x + b.x,this->y + b.y,this->z + b.z);
	return v;
}


Vector3d Vector3d::operator-(const Vector3d& b)
{
	Vector3d v;
	v.setComps(this->x - b.x,this->y - b.y,this->z - b.z);
	return v;
}

void Vector3d::fprintVector3d(FILE * fp)
{
	fprintf(fp, "%f %f %f ", this->x, this->y, this->z);
}

void Vector3d::fprintVector3d255(FILE * fp)
{
	fprintf(fp, "%d %d %d ", (int)(this->x * 255.0f), (int)(this->y * 255.0f), (int)(this->z * 255.0f));
}

float Vector3d::Mag() {
	return sqrt(*this * *this);
}

void Vector3d::Normalize()
{
	this->x *= (1.0f/Mag());
	this->y *= (1.0f/Mag());
	this->z *= (1.0f/Mag());
}

