#include "pch.h"
#include "LightSource.h"

LightSource::LightSource(Vector3D point, Color intensity)
{
	this->point = point;
	this->intensity = intensity;
}
