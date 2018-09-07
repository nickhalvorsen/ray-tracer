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
	// The reflection index is a value between 0 and 1.
	// 0 = no reflection, 1 = totally reflective
	void setReflectionIndex(float reflectionAmount);
	float getReflectionIndex();
	bool intersects(Segment3D segment);

	virtual bool getClosestIntersection(Ray ray, Vector3D& intersectionPoint, double& intersectionDistance) = 0;
	virtual Vector3D getNormal(Vector3D pointOnObject) = 0;
private:
	float _reflectionIndex;
};