#include "pch.h"
#include "Sphere.h"
#include <math.h>
#include <algorithm>

Sphere::Sphere(int id, Vector3D center, double radius, Color color)
{
	this->id = id;
	this->center = center;
	this->radius = radius;
	this->color = color;
}

Sphere::Sphere() : Sphere(0, Vector3D(0, 0, 0), 1, Color(0, 0, 0)) { }

// Algorithm reference: http://www.r-5.org/files/books/computers/algo-list/realtime-3d/Christer_Ericson-Real-Time_Collision_Detection-EN.pdf page 178
bool Sphere::getClosestIntersection(Ray ray, Vector3D& intersectionPoint, double& intersectionDistance)
{
	Vector3D m = ray.origin - center;
	double b = m.dot(ray.getDirection());
	double c = m.dot(m) - radius * radius;

	if (c > 0.0 && b > 0.0)
	{
		return false;
	}

	// Exit if r’s origin outside s (c > 0) and r pointing away from s (b > 0)
	if (c > 0.0f && b > 0.0)
	{
		return false;
	}

	float discr = b * b - c;

	// A negative discriminant corresponds to ray missing sphere
	if (discr < 0.0)
	{
		return false;
	}

	// Ray now found to intersect sphere, compute smallest t value of intersection
	double distance = -b - sqrt(discr);

	// If t is negative, ray started inside sphere so clamp t to zero
	intersectionDistance = std::max(distance, 0.0);
	intersectionPoint = ray.pointAlongRay(intersectionDistance);

	return true;
}

Vector3D Sphere::getNormal(Vector3D pointOnSurface)
{
	return (pointOnSurface - center).normalized();
}