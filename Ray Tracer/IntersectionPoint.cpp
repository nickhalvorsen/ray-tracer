#include "pch.h"
#include "IntersectionPoint.h"

IntersectionPoint::IntersectionPoint(Vector3D point, double distanceFromRayOrigin)
{
	this->point = point;
	this->distance = distanceFromRayOrigin;
}

IntersectionPoint::IntersectionPoint() : IntersectionPoint(Vector3D(0, 0, 0), -1) { }