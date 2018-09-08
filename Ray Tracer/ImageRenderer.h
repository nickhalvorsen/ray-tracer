#pragma once

#include "Bitmap.h"
#include "RayTracer.h"

class ImageRenderer
{
public:
	ImageRenderer(int threadCount);
	void renderPictureToFile(RayTracer* rayTracer, int imageWidth, int imageHeight, char* filename);
private:
	int _threadCount;
	static void renderPixel(RayTracer* rayTracer, Bitmap* bitmap, int imageWidth, int imageHeight, int x, int y);
};