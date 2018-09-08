#include "pch.h"
#include "Quad.h"


Quad::Quad(int id, Vector3D point1, Vector3D point2, Vector3D point3, Vector3D point4, Color color, float reflectionIndex)
{
	this->id = id;
	this->color = color;
	this->setReflectionIndex(reflectionIndex);

	this->_t1 = Triangle(-1, point1, point2, point3, color, reflectionIndex);
	this->_t2 = Triangle(-1, point1, point3, point4, color, reflectionIndex);
}


bool Quad::getClosestIntersection(Ray ray, Vector3D& intersectionPoint, double& intersectionDistance)
{
	if (_t1.getClosestIntersection(ray, intersectionPoint, intersectionDistance)
		|| _t2.getClosestIntersection(ray, intersectionPoint, intersectionDistance))
	{
		return true;
	}

	return false;
}

Vector3D Quad::getNormal(Vector3D pointOnObject)
{
	// here we assume the quad is on a single plane
	// so we just get the normal of the first triangle.
	return _t1.getNormal(pointOnObject);
}
