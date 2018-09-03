#pragma once

#include "Ray.h"


class Segment3D
{
public:
	Segment3D(Ray ray, double distance);
	Ray ray;
	double distance;
};