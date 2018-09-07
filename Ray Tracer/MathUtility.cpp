#pragma once

#include "pch.h"
#include "MathUtility.h"

#include <algorithm>


float MathUtility::clamp(float number, float lowBound, float highBound)
{
	return std::max(lowBound, std::min(number, highBound));
}