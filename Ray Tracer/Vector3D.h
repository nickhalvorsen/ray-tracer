#pragma once

class Vector3D
{
public:
	Vector3D(double x, double y, double z);
	Vector3D();
	double x;
	double y;
	double z;
	double getLength();
	Vector3D normalized();
	double dot(Vector3D other);
	friend Vector3D operator+(Vector3D& first, Vector3D second);
	friend Vector3D operator-(Vector3D& first, Vector3D second);
	friend Vector3D operator*(Vector3D vector, double multiplyFactor);
private:
};