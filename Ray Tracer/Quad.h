#pragma once

#include "SceneObject.h"
#include "Color.h"
#include "Triangle.h"

#include <vector>

class Quad : public SceneObject
{
public:
	// It is recommended to have the 4 points in the same plane.
	// Otherwise this implementation will have a "crease" in it 
	// because the quad is made up of 2 triangles 
	Quad(int id, Vector3D point1, Vector3D point2, Vector3D point3, Vector3D point4, Color color);

	bool getClosestIntersection(Ray ray, Vector3D& intersectionPoint, double& intersectionDistance);
	Vector3D getNormal(Vector3D pointOnObject);
private:
	Triangle _t1;
	Triangle _t2;
};