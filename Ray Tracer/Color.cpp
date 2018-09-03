#include "pch.h"
#include "Color.h"
#include <algorithm>

// todo handle clamping values between 0-255

Color::Color(unsigned char r, unsigned char g, unsigned char b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}

Color::Color()
{
	r = 0;
	g = 0;
	b = 0;
}

Color Color::add(Color other)
{
	unsigned char newR = std::min(r + other.r, 255);
	unsigned char newG = std::min(g + other.g, 255);
	unsigned char newB = std::min(b + other.b, 255);
	return Color(newR, newG, newB);
}