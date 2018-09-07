#pragma once

#include "Bitmap.h"
#include "RayTracer.h"

class RenderedImage
{
public:
	RenderedImage(RayTracer* rayTracer, int imageWidth, int imageHeight);
	void renderPixel(int x, int y);
	void saveImage(char* filename);
private:
	int imageWidth;
	int imageHeight;
	Bitmap bitmap;
	RayTracer* rayTracer;
};