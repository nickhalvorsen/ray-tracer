#include "pch.h"
#include "SceneObject.h"

int SceneObject::getId()
{
	return id;
}

bool SceneObject::intersects(Segment3D segment)
{
	Vector3D dummy;
	double intersectionDistance;
	if (getClosestIntersection(segment.ray, dummy, intersectionDistance)
		&& intersectionDistance < segment.distance)
	{
		return true;
	}

	return false;
}
