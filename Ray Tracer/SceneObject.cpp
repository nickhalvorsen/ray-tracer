#include "pch.h"
#include "SceneObject.h"
#include "MathUtility.h"
#include <algorithm>

int SceneObject::getId()
{
	return id;
}

void SceneObject::setReflectionIndex(float reflectionIndex)
{
	_reflectionIndex = MathUtility::clamp(reflectionIndex, 0.0f, 1.0f);
}

float SceneObject::getReflectionIndex()
{
	return _reflectionIndex;
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
