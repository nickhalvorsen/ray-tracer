#pragma once

#include "pch.h"
#include "MathUtility.h"

#include <algorithm>

using std::max;

float MathUtility::clamp(float number, float lowBound, float highBound)
{
	return max(lowBound, std::min(number, highBound));
}