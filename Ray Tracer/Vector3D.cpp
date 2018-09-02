#include "pch.h"
#include "Vector3D.h"
#include <math.h>


Vector3D::Vector3D(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

double Vector3D::getLength()
{
	return sqrt(x*x + y*y + z*z);
}

Vector3D Vector3D::normalized()
{
	double length = getLength();
	return Vector3D(x / length, y / length, z / length);
}

double Vector3D::dot(Vector3D other)
{
	return x*other.x + y*other.y + z*other.z;
}

Vector3D operator+(Vector3D & first, Vector3D second)
{
	return Vector3D(first.x + second.x, first.y + second.y, first.z + second.z);
}

Vector3D operator-(Vector3D & first, Vector3D second)
{
	return Vector3D(first.x - second.x, first.y - second.y, first.z - second.z);
}

Vector3D operator*(Vector3D vector, double multiplyFactor)
{
	return Vector3D(vector.x * multiplyFactor, vector.y * multiplyFactor, vector.z * multiplyFactor);
}
