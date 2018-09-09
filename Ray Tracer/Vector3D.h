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
	double dot(const Vector3D& other) const;
	Vector3D cross(const Vector3D& other) const;
	Vector3D operator+(const Vector3D& other) const;
	Vector3D operator-(const Vector3D& other) const;
	Vector3D operator*(double multiplyFactor) const;
	Vector3D operator*(const Vector3D& other) const;
	bool operator==(const Vector3D& other) const;
};