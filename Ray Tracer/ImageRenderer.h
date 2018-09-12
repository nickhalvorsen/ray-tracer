#pragma once

#include <string>
#include <memory>
class RayTracer;
class Bitmap;

class ImageRenderer
{
public:
	ImageRenderer(int threadCount);
	void renderPictureToFile(std::shared_ptr<RayTracer> rayTracer, int imageWidth, int imageHeight, std::string filename);
private:
	int _threadCount;
	static void renderPixel(std::shared_ptr<RayTracer> rayTracer, std::shared_ptr<Bitmap> bitmap, int imageWidth, int imageHeight, int x, int y);
	std::shared_ptr<Bitmap> renderPictureWithThreading(std::shared_ptr<RayTracer> rayTracer, int imageWidth, int imageHeight);
	std::shared_ptr<Bitmap> renderPictureNoThreading(std::shared_ptr<RayTracer> rayTracer, int imageWidth, int imageHeight);

};