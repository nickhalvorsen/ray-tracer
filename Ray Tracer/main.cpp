#include "pch.h"
#include <iostream>
#include <ctime>
#include "ImageRenderer.h"

int main()
{
	//--------------------------------------
	// change options here

	int imageWidth = 800;
	int imageHeight = 800;
	std::string filename = "C:/temp/raytrace.bmp";
	// Control the amount of subpixel sampling per pixel
	// 1 = no anti-aliasing
	// 2 = 4 samples per pixel (takes 4x as long to render)
	// 3 = 9 ... etc
	int antiAliasingFactor = 1; 
	// Amount of threads to utilize.
	// 0 = disable threading
	int threadCount = 4;

	//--------------------------------------
	// end options



	char fn[1024];
	strcpy_s(fn, filename.c_str());


	std::cout << "Rendering image to " << fn << " with options:" << std::endl
		<< "\twidth: " << imageWidth << std::endl
		<< "\theight: " << imageHeight << std::endl
		<< "\tantiAliasingFactor: " << antiAliasingFactor << std::endl
		<< "\tthreads: " << threadCount << std::endl << std::endl;



	RayTracer rt(antiAliasingFactor, 2);
	ImageRenderer r(threadCount);



	std::clock_t start;
	start = std::clock();

	r.renderPictureToFile(&rt, imageWidth, imageHeight, fn);

	double duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	std::cout << "Done. It took " << duration << " seconds." << std::endl;

}