#include "pch.h"
#include "ImageRenderer.h"
#include "Bitmap.h"
#include "RayTracer.h"
#include "ThreadPool.h"

#include <memory>
#include <thread>
#include <future>

using std::string;
using std::shared_ptr;

ImageRenderer::ImageRenderer(int threadCount)
{
	_threadCount = threadCount;
}

void ImageRenderer::renderPictureToFile(shared_ptr<RayTracer> rayTracer, int imageWidth, int imageHeight, string filename)
{
	bool useThreading = _threadCount > 0;

	shared_ptr<Bitmap> bitmap = useThreading
		? renderPictureWithThreading(rayTracer, imageWidth, imageHeight)
		: renderPictureNoThreading(rayTracer, imageWidth, imageHeight);

	bitmap->writeToFile(filename);
}

shared_ptr<Bitmap> ImageRenderer::renderPictureWithThreading(shared_ptr<RayTracer> rayTracer, int imageWidth, int imageHeight)
{
	shared_ptr<Bitmap> bitmap(new Bitmap(imageWidth, imageHeight));
	ThreadPool pool(_threadCount);

	for (int x = 0; x < imageWidth; x++)
	{
		for (int y = 0; y < imageHeight; y++)
		{
			pool.addJobToQueue([rayTracer, bitmap, imageWidth, imageHeight, x, y]() { renderPixel(rayTracer, bitmap, imageWidth, imageHeight, x, y); });
		}
	}

	pool.waitUntilComplete();
	return bitmap;
}

shared_ptr<Bitmap> ImageRenderer::renderPictureNoThreading(shared_ptr<RayTracer> rayTracer, int imageWidth, int imageHeight)
{
	shared_ptr<Bitmap> bitmap(new Bitmap(imageWidth, imageHeight));

	for (int x = 0; x < imageWidth; x++)
	{
		for (int y = 0; y < imageHeight; y++)
		{
			Color thisColor = rayTracer->renderPixel(imageWidth, imageHeight, x, y);
			bitmap->setPixel(x, y, thisColor);
		}
	}

	return bitmap;
}


void ImageRenderer::renderPixel(shared_ptr<RayTracer> rayTracer, shared_ptr<Bitmap> bitmap, int imageWidth, int imageHeight, int x, int y)
{
	Color thisColor = rayTracer->renderPixel(imageWidth, imageHeight, x, y);
	bitmap->setPixel(x, y, thisColor);
}