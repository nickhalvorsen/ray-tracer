#include "pch.h"
#include "ImageRenderer.h"
#include "Bitmap.h"
#include "RayTracer.h"
#include "ThreadPool.h"

#include <thread>
#include <future>

using std::string;

ImageRenderer::ImageRenderer(int threadCount)
{
	_threadCount = threadCount;
}

void ImageRenderer::renderPictureToFile(RayTracer* rayTracer, int imageWidth, int imageHeight, string filename)
{
	Bitmap bitmap(imageWidth, imageHeight);
	Bitmap* bptr = &bitmap;

	bool useThreader = _threadCount > 0;
	if (useThreader)
	{
		ThreadPool pool(_threadCount);

		for (int x = 0; x < imageWidth; x++)
		{
			for (int y = 0; y < imageHeight; y++)
			{
				pool.addJobToQueue([rayTracer, bptr, imageWidth, imageHeight, x, y]() { renderPixel(rayTracer, bptr, imageWidth, imageHeight, x, y); });
			}
		}

		pool.waitUntilComplete();
		bitmap.writeToFile(filename);
	}
	else
	{

		for (int x = 0; x < imageWidth; x++)
		{
			for (int y = 0; y < imageHeight; y++)
			{
				Color thisColor = rayTracer->renderPixel(imageWidth, imageHeight, x, y);
				bitmap.setPixel(x, y, thisColor);
			}
		}

		bitmap.writeToFile(filename);

	}
}

void ImageRenderer::renderPixel(RayTracer* rayTracer, Bitmap* bitmap, int imageWidth, int imageHeight, int x, int y)
{
	Color thisColor = rayTracer->renderPixel(imageWidth, imageHeight, x, y);
	bitmap->setPixel(x, y, thisColor);
}