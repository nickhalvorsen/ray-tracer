#include "pch.h"
#include <iostream>
#include <ctime>
#include "ImageRenderer.h"
#include "Sphere.h"
#include "Quad.h"
#include "LightSource.h"


std::vector<SceneObject*> getSceneObjects()
{
	std::vector<SceneObject*> sceneObjects;

	sceneObjects.push_back(new Sphere(1, Vector3D(-4, 4.4, -5), 1, Color(250, 0, 200), 0));
	sceneObjects.push_back(new Sphere(2, Vector3D(-4, 0, -5), 1, Color(250, 250, 200), 0));
	sceneObjects.push_back(new Sphere(3, Vector3D(-2.5, 1.5, -5), .2, Color(100, 250, 200), 0));
	//sceneObjects.push_back(new Sphere(3, Vector3D(2, -1.3, -2.8), .1, Color(100, 88, 255), 0));
	sceneObjects.push_back(new Sphere(4, Vector3D(0, 0, -5), 1, Color(255, 255, 255), .4));

	sceneObjects.push_back(new Quad(5, Vector3D(-4, 2, -8), Vector3D(-4, 6, -6), Vector3D(-1, 6, -6), Vector3D(-1, 2, -8), Color(255, 255, 255), 0.3));

	//sceneObjects.push_back(new Quad(6, Vector3D(-4, -2, -6.999), Vector3D(-4, 2, -7.999), Vector3D(-3.9, 2, -7.999), Vector3D(-3.9, -2, -6.999), Color(0, 0, 0), 0));
	//sceneObjects.push_back(new Quad(6, Vector3D(-4, 1.9, -7.999), Vector3D(-4, 2, -7.999), Vector3D(-1, 2, -7.999), Vector3D(-1, 1.9, -7.999), Color(0, 0, 0), 0));


	// generate a grid of 1x1 quads
	int startX = -5;
	int startZ = -10;
	int y = -2;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			Color c;
			if ((i+j) % 2 == 0)
			{
				c = Color(250, 250, 250);
			}
			else
			{
				c = Color(2, 2, 2);
			}

			sceneObjects.push_back(new Quad(100+i*10+j, Vector3D(startX+i, y, startZ+j+1), Vector3D(startX+i, y, startZ+j), Vector3D(startX+i+1, y, startZ+j), Vector3D(startX+i+1, y, startZ+j+1), c, 0));

		}
	}


	return sceneObjects;
}

std::vector<LightSource> getLightSources()
{
	std::vector<LightSource> lightSources;
	lightSources.push_back(LightSource(Vector3D(1, 8, -5), Color(255, 255, 255)));
	return lightSources;
}

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
	int antiAliasingFactor = 0;
	// maximum reflection depth
	int maxReflectionDepth = 3;
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
		<< "\tmaxReflectionDepth: " << antiAliasingFactor << std::endl
		<< "\tthreads: " << threadCount << std::endl << std::endl;

	std::vector<SceneObject*> sceneObjects = getSceneObjects();

	RayTracer rt(antiAliasingFactor, maxReflectionDepth, getSceneObjects(), getLightSources());
	ImageRenderer r(threadCount);



	std::clock_t start;
	start = std::clock();

	r.renderPictureToFile(&rt, imageWidth, imageHeight, fn);

	double duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	std::cout << "Done. It took " << duration << " seconds." << std::endl;

	// delete scene objects
	for (int i = 0; i < sceneObjects.size(); ++i) {
		delete sceneObjects[i];
	}
	sceneObjects.clear();
}