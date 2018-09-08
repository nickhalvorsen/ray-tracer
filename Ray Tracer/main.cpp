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

	sceneObjects.push_back(new Sphere(1, Vector3D(-5, 5, -5), 1, Color(250, 0, 200), 0));
	sceneObjects.push_back(new Sphere(2, Vector3D(-5, 0, -5), 1, Color(250, 250, 200), 0));
	sceneObjects.push_back(new Sphere(3, Vector3D(-3, 1.5, -5), .2, Color(100, 250, 200), 0));
	sceneObjects.push_back(new Sphere(4, Vector3D(0, 0, -5), 1, Color(255, 255, 255), .4));
	sceneObjects.push_back(new Quad(5, Vector3D(-5, -1, 5), Vector3D(-5, -1, -5), Vector3D(5, -1, -5), Vector3D(5, -1, 5), Color(200, 177, 12), 0));

	return sceneObjects;
}

std::vector<LightSource> getLightSources()
{
	std::vector<LightSource> lightSources;
	lightSources.push_back(LightSource(Vector3D(1, 5, -5), Color(255, 255, 255)));
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

	std::vector<SceneObject*> sceneObjects = getSceneObjects();

	RayTracer rt(antiAliasingFactor, 2, getSceneObjects(), getLightSources());
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