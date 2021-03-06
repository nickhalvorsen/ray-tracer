#include "pch.h"
#include <iostream>
#include <string>
#include <ctime>
#include <memory>
#include "ImageRenderer.h"
#include "RayTracer.h"
#include "Sphere.h"
#include "Quad.h"
#include "LightSource.h"

using std::vector;
using std::string;
using std::shared_ptr;
using std::cout;
using std::endl;
using std::clock;
using std::clock_t;

vector<shared_ptr<SceneObject>> getSampleSceneObjects()
{
	vector<shared_ptr<SceneObject>> sceneObjects;

	sceneObjects.push_back(shared_ptr<SceneObject>(new Sphere(1, Vector3D(-4, 4.4, -5), 1, Color(250, 0, 200), 0)));
	sceneObjects.push_back(shared_ptr<SceneObject>(new Sphere(2, Vector3D(-4, 0, -5), 1, Color(250, 250, 200), 0)));
	sceneObjects.push_back(shared_ptr<SceneObject>(new Sphere(3, Vector3D(-2.5, 1.5, -5), .2, Color(100, 250, 200), 0)));
	sceneObjects.push_back(shared_ptr<SceneObject>(new Sphere(4, Vector3D(0, 0, -5), 1, Color(255, 255, 255), .4)));
	sceneObjects.push_back(shared_ptr<SceneObject>(new Quad(5, Vector3D(-4, 2, -8), Vector3D(-4, 6, -6), Vector3D(-1, 6, -6), Vector3D(-1, 2, -8), Color(255, 255, 255), 0.3)));

	// generate a grid of 1x1 tiles (quads)
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

			//sceneObjects.push_back(new Quad(100+i*10+j, Vector3D(startX+i, y, startZ+j+1), Vector3D(startX+i, y, startZ+j), Vector3D(startX+i+1, y, startZ+j), Vector3D(startX+i+1, y, startZ+j+1), c, 0));
		}
	}


	return sceneObjects;
}

vector<LightSource> getSampleLightSources()
{
	vector<LightSource> lightSources;
	lightSources.push_back(LightSource(Vector3D(1, 8, -5), Color(255, 255, 255)));
	return lightSources;
}

int main()
{
	//--------------------------------------
	// change options here

	int imageWidth = 800;
	int imageHeight = 800;
	string filename = "C:/temp/raytrace.bmp";
	// Control the amount of subpixel sampling per pixel
	// 1 = no anti-aliasing
	// 2 = 4 samples per pixel (takes 4x as long to render)
	// 3 = 9 ... etc
	int antiAliasingFactor = 1;
	// maximum reflection depth
	int maxReflectionDepth = 3;
	// Amount of threads to utilize.
	// 0 = disable threading
	int threadCount = 4;

	//--------------------------------------
	// end options



	cout << "Rendering image to " << filename << " with options:" << endl
		<< "\twidth: " << imageWidth << endl
		<< "\theight: " << imageHeight << endl
		<< "\tantiAliasingFactor: " << antiAliasingFactor << endl
		<< "\tmaxReflectionDepth: " << antiAliasingFactor << endl
		<< "\tthreads: " << threadCount << endl << endl;

	vector<shared_ptr<SceneObject>> sceneObjects = getSampleSceneObjects();
	vector<LightSource> lightSources = getSampleLightSources();
	shared_ptr<RayTracer> rt(new RayTracer(antiAliasingFactor, maxReflectionDepth, sceneObjects, lightSources));
	ImageRenderer r(threadCount);

	clock_t start = clock();

	r.renderPictureToFile(rt, imageWidth, imageHeight, filename);

	double duration = (clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "Done. It took " << duration << " seconds." << endl;
}