#pragma once

#include <vector>
#include "Color.h"

class Bitmap
{
public:
	Bitmap(int width, int height);
	~Bitmap();
	void setPixel(int x, int y, Color color);
	Color getPixel(int x, int y);
	int getWidth();
	int getHeight();
	void writeToFile(char* filename);
private:
	static int const bytesPerPixel;
	static Color const defaultColor;
	int width;
	int height;
	// Blue, green, and red values are stored for each pixel
	// as consecutive unsigned chars (0-255) in the array.
	// It is stored as BGR because that is how it's written to a bitmap file.
	unsigned char* pixels;

	bool isWithinImage(int x, int y);
	int arrayIndexForCoordinates(int x, int y);
};