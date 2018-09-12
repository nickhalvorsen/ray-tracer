#pragma once

#include <string>
class RayTracer;
class Bitmap;

class ImageRenderer
{
public:
	ImageRenderer(int threadCount);
	void renderPictureToFile(RayTracer* rayTracer, int imageWidth, int imageHeight, std::string filename);
private:
	int _threadCount;
	static void renderPixel(RayTracer* rayTracer, Bitmap* bitmap, int imageWidth, int imageHeight, int x, int y);
};