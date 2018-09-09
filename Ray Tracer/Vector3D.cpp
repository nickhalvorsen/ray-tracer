#include "pch.h"
#include "Vector3D.h"
#include <math.h>


Vector3D::Vector3D(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3D::Vector3D() : Vector3D(0, 0, 0) { }

double Vector3D::getLength()
{
	return sqrt(x*x + y*y + z*z);
}

Vector3D Vector3D::normalized()
{
	double length = getLength();
	return Vector3D(x / length, y / length, z / length);
}

double Vector3D::dot(const Vector3D& other) const
{
	return x*other.x + y*other.y + z*other.z;
}

Vector3D Vector3D::cross(const Vector3D&  other) const
{
	double tempX = y * other.z - z * other.y;
	double tempY = z * other.x - x * other.z;
	double tempZ = x * other.y - y * other.x;
	return Vector3D(tempX, tempY, tempZ);
}

Vector3D Vector3D::operator+(const Vector3D& other) const
{
	return Vector3D(x + other.x, y + other.y, z + other.z);
}

Vector3D Vector3D::operator-(const Vector3D& other) const
{
	return Vector3D(x - other.x, y - other.y, z - other.z);
}

Vector3D Vector3D::operator*(double multiplyFactor) const
{
	return Vector3D(x * multiplyFactor, y * multiplyFactor, z * multiplyFactor);
}

Vector3D Vector3D::operator*(const Vector3D& other) const
{
	return Vector3D(x * other.x, y * other.y, z * other.z);
}

bool Vector3D::operator==(const Vector3D& other) const 
{
	return x == other.x
		&& y == other.y
		&& z == other.z;
}
