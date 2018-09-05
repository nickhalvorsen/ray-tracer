#pragma once
class Color
{
public:
	Color(int r, int g, int b);
	Color();
	int r;
	int g;
	int b;
	Color add(Color other);
	bool operator==(Color other);
	Color operator*(double coefficient);
	Color operator+(Color other);
	Color operator+=(Color other);
private:
	int validateRgb(int rgb);
};

