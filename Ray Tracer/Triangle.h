#pragma once

#include "SceneObject.h"
#include "Color.h"
#include "Vector3D.h"
#include "Ray.h"
#include "Segment3D.h"

#include <vector>

class Triangle : public SceneObject
{
public:
	Triangle();
	Triangle(int id, Vector3D point1, Vector3D point2, Vector3D point3, Color color, float reflectionIndex);

	bool getClosestIntersection(Ray ray, Vector3D& intersectionPoint, double& intersectionDistance);
	Vector3D getNormal(Vector3D pointOnObject);
private:
	Vector3D _point1;
	Vector3D _point2;
	Vector3D _point3;
};