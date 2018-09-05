#pragma once

#include "Color.h"
#include "Vector3D.h"
#include "Segment3D.h"

class SceneObject
{
public:
	int id;
	Color color;

	int getId();

	virtual bool getClosestIntersection(Ray ray, Vector3D& intersectionPoint, double& intersectionDistance) = 0;
	virtual Vector3D getNormal(Vector3D pointOnObject) = 0;
	virtual bool intersects(Segment3D segment) = 0;
};