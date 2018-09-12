#include "pch.h"
#include "SceneObject.h"
#include "MathUtility.h"
#include <algorithm>

int SceneObject::getId()
{
	return id;
}

void SceneObject::setReflectionIndex(double reflectionIndex)
{
	_reflectionIndex = MathUtility::clampDouble(reflectionIndex, 0.0f, 1.0f);
}

double SceneObject::getReflectionIndex()
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
