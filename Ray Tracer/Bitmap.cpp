#include "pch.h"
#include "Bitmap.h"
#include "Color.h"

#include <Windows.h>
#include <fstream>

const Color Bitmap::defaultColor = Color(0, 0, 0);
const int Bitmap::bytesPerPixel = 3;

Bitmap::Bitmap(int width, int height) 
{
	// todo: remove this and add padding to data array 
	// https://stackoverflow.com/questions/29440672/bmp-file-line-padding-issue#29440863
	if ((width * bytesPerPixel) % 4 != 0) {
		throw new std::exception("error: image row bytes must be multiple of 4: this is a restriction of the BMP file type"); 
	}

	this->width = width;
	this->height = height;

	int arrayLength = width*height*bytesPerPixel;

	pixels = new unsigned char[arrayLength] { 0 };
}

Bitmap::Bitmap() : Bitmap(0, 0) { }

Bitmap::~Bitmap()
{
	delete[] pixels;
}

void Bitmap::setPixel(int x, int y, Color color)
{
	if (!validCoords(x, y)) {
		throw std::invalid_argument("given coordinates outside image bounds");
	}

	int index = arrayIndexForCoords(x, y);

	pixels[index] = color.b;
	pixels[index + 1] = color.g;
	pixels[index + 2] = color.r;
}

bool Bitmap::validCoords(int x, int y) {
	return x >= 0 && x < width
		&& y >= 0 && y < height;
}

int Bitmap::arrayIndexForCoords(int x, int y) {
	if (!validCoords(x, y)) {
		throw std::invalid_argument("given coordinates outside image bounds");
	}

	return y * width * bytesPerPixel + x * bytesPerPixel;
}

Color Bitmap::getPixel(int x, int y)
{
	if (!validCoords(x, y))
	{
		throw std::invalid_argument("given coordinates outside image bounds");
	}

	int index = arrayIndexForCoords(x, y);

	unsigned char b = pixels[index];
	unsigned char g = pixels[index + 1];
	unsigned char r = pixels[index + 2];

	return Color(r, g, b);
}

int Bitmap::getWidth()
{
	return width;
}

int Bitmap::getHeight()
{
	return height;
}

void Bitmap::writeToFile(char* filename)
{
	FILE *file;
	errno_t err = fopen_s(&file, filename, "wb");

	if (!file) {
		throw std::exception("error opening file for write");
	}

	BITMAPFILEHEADER fileHeader;
	// Bitmap headers must follow a specific format
	fileHeader.bfSize = sizeof(BITMAPFILEHEADER);
	fileHeader.bfType = 0x4D42;
	fileHeader.bfReserved1 = 0;
	fileHeader.bfReserved2 = 0;
	fileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	BITMAPINFOHEADER infoHeader;
	infoHeader.biSize = sizeof(BITMAPINFOHEADER);
	infoHeader.biPlanes = 1;
	infoHeader.biBitCount = 24;	
	infoHeader.biCompression = BI_RGB;
	infoHeader.biSizeImage = width * abs(height) * bytesPerPixel;
	infoHeader.biXPelsPerMeter = 0;
	infoHeader.biYPelsPerMeter = 0;
	infoHeader.biClrUsed = 0;
	infoHeader.biClrImportant = 0;
	infoHeader.biWidth = width;
	// bitmap is stored "upside down" on disk. we use -height to make it display right side up   
	infoHeader.biHeight = -height;

	fwrite(&fileHeader, 1, sizeof(BITMAPFILEHEADER), file);
	fwrite(&infoHeader, 1, sizeof(BITMAPINFOHEADER), file);
	fwrite(pixels, 1, infoHeader.biSizeImage, file);

	fclose(file);
}