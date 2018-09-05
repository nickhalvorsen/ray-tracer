#pragma once

#include "SceneObject.h"
#include "Color.h"
#include "Vector3D.h"
#include "Ray.h"
#include "Segment3D.h"

#include <vector>

class Sphere : public SceneObject
{
public:
	Sphere();
	Sphere(int id, Vector3D center, double radius, Color color);

	Vector3D center;
	double radius;

	bool getClosestIntersection(Ray ray, Vector3D& intersectionPoint, double& intersectionDistance);
	Vector3D getNormal(Vector3D pointOnObject);
	bool intersects(Segment3D segment);

	bool operator==(Sphere& other);
};