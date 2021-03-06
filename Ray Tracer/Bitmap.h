#pragma once

#include <vector>
#include "Color.h"

class Bitmap
{
public:
	Bitmap(int width, int height);
	Bitmap();
	~Bitmap();
	void setPixel(int x, int y, Color color);
	Color getPixel(int x, int y);
	int getWidth();
	int getHeight();
	void writeToFile(std::string filename);
private:
	static int const _bytesPerPixel;
	static Color const _defaultColor;
	int _width;
	int _height;
	// Blue, green, and red values are stored for each pixel
	// as consecutive unsigned chars (0-255) in the array.
	// It is stored as BGR because that is how it's written to a bitmap file.
	unsigned char* _pixels;

	bool validCoords(int x, int y);
	int arrayIndexForCoords(int x, int y);
};