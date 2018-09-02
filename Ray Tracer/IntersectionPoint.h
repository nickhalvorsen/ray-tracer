#pragma once

#include "Vector3D.h"

class IntersectionPoint
{
public:
	IntersectionPoint(Vector3D point, double distanceFromRayOrigin);
	IntersectionPoint();
	Vector3D point;
	double distance;
private:
};