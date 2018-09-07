#pragma once

#include "Bitmap.h"
#include "RayTracer.h"

class ImageRenderer
{
public:
	void renderPictureToFile(RayTracer* rayTracer, int imageWidth, int imageHeight, char* filename);
private:
	static void renderPixel(RayTracer* rayTracer, Bitmap* bitmap, int imageWidth, int imageHeight, int x, int y);
};