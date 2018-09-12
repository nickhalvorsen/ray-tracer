#include "pch.h"
#include "Color.h"
#include "MathUtility.h"
#include <algorithm>

Color::Color(int r, int g, int b)
{
	this->r = validateRgb(r);
	this->g = validateRgb(g);
	this->b = validateRgb(b);
}

Color::Color()
{
	r = 0;
	g = 0;
	b = 0;
}

Color Color::add(Color other)
{
	return Color(r + other.r, g + other.g, b + other.b);
}

bool Color::operator==(Color other)
{
	return r == other.r
		&& g == other.g
		&& b == other.b;
}

Color Color::operator*(double coefficient)
{
	int newR = (int)(r * coefficient);
	int newG = (int)(g * coefficient);
	int newB = (int)(b * coefficient);
	return Color(newR, newG, newB);
}

Color Color::operator+(Color other)
{
	return Color(r + other.r, g + other.g, b + other.b);
}

Color Color::operator+=(Color other)
{
	r = validateRgb(r + other.r);
	g = validateRgb(g + other.g);
	b = validateRgb(b + other.b);
	return *this;
}

int Color::validateRgb(int rgb)
{
	return MathUtility::clampInt(rgb, 0, 255);
}