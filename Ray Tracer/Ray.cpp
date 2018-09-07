#include "pch.h"
#include "Ray.h"

Ray::Ray(Vector3D origin, Vector3D direction)
{
	this->origin = origin;
	this->_direction = direction.normalized();
}

Ray::Ray() : Ray(Vector3D(), Vector3D()) { }

Vector3D Ray::getDirection() 
{
	return _direction;
}

Vector3D Ray::pointAlongRay(double distanceFromOrigin)
{
	return origin + _direction * distanceFromOrigin;
}