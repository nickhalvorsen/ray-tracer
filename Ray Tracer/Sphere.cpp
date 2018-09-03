#include "pch.h"
#include "Sphere.h"
#include <math.h>
#include <algorithm>

Sphere::Sphere(Vector3D center, double radius, Color color)
{
	this->center = center;
	this->radius = radius;
	this->color = color;
}

Sphere::Sphere() : Sphere(Vector3D(0, 0, 0), 1, Color(0, 0, 0)) { }

//http://www.r-5.org/files/books/computers/algo-list/realtime-3d/Christer_Ericson-Real-Time_Collision_Detection-EN.pdf page 178
bool Sphere::getClosestIntersection(Ray ray, IntersectionPoint& intersectionPoint)
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
	distance = std::max(distance, 0.0);
	Vector3D point = ray.pointAlongRay(distance);

	intersectionPoint = IntersectionPoint(point, distance);

	return true;
}

/*

t = distance of intersection along ray 

d = diretion vector

// Intersects ray r = p + td, |d| = 1, with sphere s and, if intersecting,
// returns t value of intersection and intersection point q
int IntersectRaySphere(Point p, Vector d, Sphere s, float &t, Point &q)
{



// Exit if r’s origin outside s (c > 0) and r pointing away from s (b > 0)
if (c > 0.0f && b > 0.0f) return 0;
float discr = b*b - c;

// A negative discriminant corresponds to ray missing sphere
if (discr < 0.0f) return 0;

// Ray now found to intersect sphere, compute smallest t value of intersection
t = -b - Sqrt(discr);

// If t is negative, ray started inside sphere so clamp t to zero
if (t < 0.0f) t = 0.0f;
q = p + t * d;

return 1;
}


*/