#include "pch.h"
#include "Triangle.h"
#include <math.h>
#include <algorithm>


Triangle::Triangle(int id, Vector3D point1, Vector3D point2, Vector3D point3, Color color, float reflectionIndex)
{
	this->id = id;
	this->_point1 = point1;
	this->_point2 = point2;
	this->_point3 = point3;
	this->color = color;
	setReflectionIndex(reflectionIndex);
}

Triangle::Triangle() : Triangle(-1, Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), Color(0, 0, 0), 0) { }

bool Triangle::getClosestIntersection(Ray ray, Vector3D& intersectionPoint, double& intersectionDistance)
{
	Vector3D v0 = _point1;
	Vector3D v1 = _point2;
	Vector3D v2 = _point3;

	// compute plane's normal
	Vector3D v0v1 = v1 - v0;
	Vector3D v0v2 = v2 - v0;
	// no need to normalize
	Vector3D N = v0v1.cross(v0v2); // N
	float area2 = N.getLength();

	// Step 1: finding P

	// check if ray and plane are parallel ?
	float NdotRayDirection = N.dot(ray.getDirection());
	float kEpsilon = 0.00001;
	if (fabs(NdotRayDirection) < kEpsilon) // almost 0
		return false; // they are parallel so they don't intersect !

		// compute d parameter using equation 2
	float d = N.dot(v0);

	// compute t (equation 3)
	float t = (N.dot(ray.origin) + d) / NdotRayDirection;
	// check if the triangle is in behind the ray
	if (t < 0) return false; // the triangle is behind

	// compute the intersection point using equation 1
	Vector3D P = ray.origin + ray.getDirection()* t;

	// Step 2: inside-outside test
	Vector3D C; // vector perpendicular to triangle's plane

	// edge 0
	Vector3D edge0 = v1 - v0;
	Vector3D vp0 = P - v0;
	C = edge0.cross(vp0);
	if (N.dot(C) < 0) return false; // P is on the right side

	// edge 1
	Vector3D edge1 = v2 - v1;
	Vector3D vp1 = P - v1;
	C = edge1.cross(vp1);
	if (N.dot(C) < 0) return false; // P is on the right side

	// edge 2
	Vector3D edge2 = v0 - v2;
	Vector3D vp2 = P - v2;
	C = edge2.cross(vp2);
	if (N.dot(C) < 0) return false; // P is on the right side;

	intersectionPoint = P;
	intersectionDistance = (intersectionPoint - ray.origin).getLength();
	if (intersectionDistance < 0)
		intersectionDistance = -intersectionDistance;

	return true; // this ray hits the triangle
}

// To calculate the normal it is not necessary to use the value passed in
Vector3D Triangle::getNormal(Vector3D pointOnObject)
{
	// The cross product of any two vectors on the plane
	// will yield the normal vector.

	Vector3D v1 = _point3 - _point2;
	Vector3D v2 = _point3 - _point1;

	
	return v1.cross(v2).normalized();
}