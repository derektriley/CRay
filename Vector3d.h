#include <cstdio>

class Vector3d
{
	public:
		Vector3d(); //Default constructor
		Vector3d(float x, float y, float z);
		Vector3d operator+(const Vector3d& b);
		Vector3d operator-(const Vector3d& b);
		float Mag();
		void Normalize();
		void setComps(float x, float y, float z);
		void fprintVector3d(FILE * fp);
		void fprintVector3d255(FILE * fp);
		float x;
		float y;
		float z;
};

inline float operator*(const Vector3d &b, const Vector3d &y)
{
	return ((b.x * y.x) + (b.y * y.y) + (b.z * y.z)); //Dot product of two Vector3d's
}

inline Vector3d operator*(float b, const Vector3d &y)
{
	Vector3d v;
	v.setComps(y.x * b, y.y * b, y.z * b);
	return v;
}

inline Vector3d operator*(const Vector3d &y, float b)
{
	Vector3d v;
	v.setComps(y.x * b, y.y * b, y.z * b);
	return v;
}

inline Vector3d operator/(const Vector3d &y, float b)
{
	Vector3d v;
	v.setComps(y.x / b, y.y / b, y.z / b);
	return v;
}

inline Vector3d operator/(float b, const Vector3d &y)
{
	Vector3d v;
	v.setComps(y.x / b, y.y / b, y.z / b);
	return v;
}
