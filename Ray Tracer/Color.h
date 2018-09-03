#pragma once
class Color
{
public:
	Color(unsigned char, unsigned char, unsigned char);
	Color();
	unsigned char r;
	unsigned char g;
	unsigned char b;
	Color add(Color other);
	bool operator==(Color other);
};

