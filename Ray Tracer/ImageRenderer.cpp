#include "pch.h"
#include "ImageRenderer.h"
#include "Bitmap.h"
#include "RayTracer.h"
#include "Threader.h"

ImageRenderer::ImageRenderer() 
{

}

void ImageRenderer::renderPictureToFile(int imageWidth, int imageHeight, char* filename)
{
	Bitmap bitmap(imageWidth, imageHeight);
	RayTracer rayTracer;

	for (int x = 0; x < imageWidth; x++)
	{
		for (int y = 0; y < imageHeight; y++)
		{
			Color thisColor = rayTracer.renderPixel(imageWidth, imageHeight, x, y);
			bitmap.setPixel(x, y, thisColor);
		}
	}

	bitmap.writeToFile(filename);
}