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
	Sphere(Vector3D center, double radius);
	Vector3D center;
	double radius;
	Color color;
	bool getClosestIntersection(Ray ray, IntersectionPoint& point);

private:

};