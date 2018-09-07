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
	double dot(const Vector3D other) const;
	Vector3D cross(Vector3D other);
	Vector3D operator+(Vector3D other);
	Vector3D operator-(Vector3D other);
	Vector3D operator*(double multiplyFactor);
	Vector3D operator*(Vector3D other);
	bool operator==(Vector3D other);
};