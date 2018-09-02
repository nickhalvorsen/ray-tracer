#include "pch.h"
#include "Color.h"

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