#pragma once

#include "Vector3D.h"

class Ray
{
public:
	Ray();
	Ray(Vector3D origin, Vector3D direction);
	Vector3D origin;
	Vector3D getDirection();
	Vector3D pointAlongRay(double distanceFromOrigin);
private:
	Vector3D _direction;
};