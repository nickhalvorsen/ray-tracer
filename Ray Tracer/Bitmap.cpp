#include "pch.h"
#include "Bitmap.h"
#include "Color.h"

#include <Windows.h>
#include <fstream>

using std::string;
using std::exception;
using std::invalid_argument;

const Color Bitmap::_defaultColor = Color(0, 0, 0);
const int Bitmap::_bytesPerPixel = 3;

Bitmap::Bitmap(int width, int height) 
{
	// todo: remove this and add padding to data array 
	if ((width * _bytesPerPixel) % 4 != 0) {
		throw new exception("error: image row bytes must be multiple of 4: this is a restriction of the BMP file type"); 
	}

	this->_width = width;
	this->_height = height;

	int arrayLength = width*height*_bytesPerPixel;

	_pixels = new unsigned char[arrayLength] { 0 };
}

Bitmap::Bitmap() : Bitmap(0, 0) { }

Bitmap::~Bitmap()
{
	delete[] _pixels;
}

void Bitmap::setPixel(int x, int y, Color color)
{
	if (!validCoords(x, y)) {
		throw invalid_argument("given coordinates outside image bounds");
	}

	int index = arrayIndexForCoords(x, y);

	_pixels[index] = color.b;
	_pixels[index + 1] = color.g;
	_pixels[index + 2] = color.r;
}

bool Bitmap::validCoords(int x, int y) 
{
	return x >= 0 && x < _width
		&& y >= 0 && y < _height;
}

int Bitmap::arrayIndexForCoords(int x, int y) 
{
	if (!validCoords(x, y)) 
	{
		throw invalid_argument("given coordinates outside image bounds");
	}

	return y * _width * _bytesPerPixel + x * _bytesPerPixel;
}

Color Bitmap::getPixel(int x, int y)
{
	if (!validCoords(x, y))
	{
		throw invalid_argument("given coordinates outside image bounds");
	}

	int index = arrayIndexForCoords(x, y);

	unsigned char b = _pixels[index];
	unsigned char g = _pixels[index + 1];
	unsigned char r = _pixels[index + 2];

	return Color(r, g, b);
}

int Bitmap::getWidth()
{
	return _width;
}

int Bitmap::getHeight()
{
	return _height;
}

void Bitmap::writeToFile(string filename)
{
	FILE *file;
	errno_t err = fopen_s(&file, filename.c_str(), "wb");

	if (!file) {
		throw exception("error opening file for write");
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
	infoHeader.biSizeImage = _width * abs(_height) * _bytesPerPixel;
	infoHeader.biXPelsPerMeter = 0;
	infoHeader.biYPelsPerMeter = 0;
	infoHeader.biClrUsed = 0;
	infoHeader.biClrImportant = 0;
	infoHeader.biWidth = _width;
	// bitmap is stored "upside down" on disk. we use -height to make it display right side up   
	infoHeader.biHeight = -_height;

	fwrite(&fileHeader, 1, sizeof(BITMAPFILEHEADER), file);
	fwrite(&infoHeader, 1, sizeof(BITMAPINFOHEADER), file);
	fwrite(_pixels, 1, infoHeader.biSizeImage, file);

	fclose(file);
}