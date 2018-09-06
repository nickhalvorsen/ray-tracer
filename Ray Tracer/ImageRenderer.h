#pragma once

#include "Bitmap.h"

class ImageRenderer
{
public:
	ImageRenderer();
	void renderPictureToFile(int imageWidth, int imageHeight, char* filename);
};