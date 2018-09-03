#include "pch.h"
#include "Segment3D.h"

Segment3D::Segment3D(Ray ray, double distance)
{
	this->ray = ray;
	this->distance = distance;
}