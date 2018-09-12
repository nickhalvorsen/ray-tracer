#pragma once

#include "pch.h"
#include "MathUtility.h"

#include <algorithm>

using std::max;

int MathUtility::clampInt(int number, int lowBound, int highBound)
{
	return max(lowBound, std::min(number, highBound));
}

double MathUtility::clampDouble(double number, double lowBound, double highBound)
{
	return max(lowBound, std::min(number, highBound));
}
