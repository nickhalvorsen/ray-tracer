#pragma once

#include "Color.h"
#include "Vector3D.h"
#include "Ray.h"
#include "IntersectionPoint.h"

#include <vector>

class Sphere
{
public:
	Sphere();
	Sphere(Vector3D center, double radius, Color color);
	Vector3D center;
	double radius;
	Color color;
	bool getClosestIntersection(Ray ray, IntersectionPoint& point);
	Vector3D getNormal(Vector3D pointOnObject);

private:

};