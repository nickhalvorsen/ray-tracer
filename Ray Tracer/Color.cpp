#include "pch.h"
#include "Color.h"
#include <algorithm>

Color::Color(int r, int g, int b)
{
	this->r = validate(r);
	this->g = validate(g);
	this->b = validate(b);
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
	return Color(r * coefficient, g * coefficient, b * coefficient);
}

Color Color::operator+(Color other)
{
	return Color(r + other.r, g + other.g, b + other.b);
}

int Color::validate(int rgb)
{
	rgb = std::min(rgb, 255);
	rgb = std::max(rgb, 0);

	return rgb;
}