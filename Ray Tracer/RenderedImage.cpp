#include "pch.h"
#include "RenderedImage.h"

RenderedImage::RenderedImage(RayTracer* rayTracer, int imageWidth, int imageHeight)
{
	this->rayTracer = rayTracer;
	this->imageWidth = imageWidth;
	this->imageHeight = imageHeight;
	this->bitmap = Bitmap(imageWidth, imageHeight);
}

void RenderedImage::renderPixel(int x, int y)
{
	Color pixelColor = rayTracer->renderPixel(imageWidth, imageHeight, x, y);
	bitmap.setPixel(x, y, pixelColor);
}

void RenderedImage::saveImage(char * filename)
{
	bitmap.writeToFile(filename);
}
