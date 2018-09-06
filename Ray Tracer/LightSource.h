#pragma once

#include "Color.h"
#include "Vector3D.h"

class LightSource
{
public:
	LightSource(Vector3D point, Color intensity);
	Vector3D point;
	Color intensity;
};