#include "pch.h"
#include "RayTracer.h"
#include "Bitmap.h"

#define _USE_MATH_DEFINES
#include <math.h>

const Color RayTracer::backgroundColor = Color(2, 2, 2);
const int RayTracer::maxDepth = 1;

RayTracer::RayTracer()
{
	sceneObjects.push_back(Sphere(Vector3D(-5, 5, -5), 1, Color(250, 200, 200)));
	sceneObjects.push_back(Sphere(Vector3D(-5, 0, -5), 1, Color(250, 250, 200)));
	sceneObjects.push_back(Sphere(Vector3D(0, 0, -5), 1, Color(200, 250, 200)));
	lightSources.push_back(Vector3D(0, .5, 3));
}

void RayTracer::renderPicture(int imageWidth, int imageHeight, char* filename) 
{
	Bitmap bitmap(imageWidth, imageHeight);

	for (int x = 0; x < imageWidth; x++)
	{
		for (int y = 0; y < imageHeight; y++) 
		{
			Color thisColor = renderPixel(imageWidth, imageHeight, x, y);
			bitmap.setPixel(x, y, thisColor);
		}
	}

	bitmap.writeToFile(filename);
}

Color RayTracer::renderPixel(int imageWidth, int imageHeight, int x, int y)
{
	Ray ray = getRayForPixel(imageWidth, imageHeight, x, y);
	return rayTrace(ray, 0);
}

// http://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays?url=3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays
Ray RayTracer::getRayForPixel(int imageWidth, int imageHeight, int x, int y)
{
	double fov = 90;
	double imageAspectRatio = imageWidth / imageHeight;
	double Px = (2 * ((x + 0.5) / imageWidth) - 1) * tan(fov / 2 * M_PI / 180) * imageAspectRatio;
	double Py = (1 - 2 * ((y + 0.5) / imageHeight) * tan(fov / 2 * M_PI / 180));

	Vector3D rayOrigin = Vector3D(0, 0, 0);
	Vector3D rayDirection = Vector3D(Px, Py, -1) - rayOrigin; // note that this just equal to Vector3D(Px, Py, -1);
	rayDirection = Vector3D(rayDirection); // it's a direction so don't forget to normalize 
	return Ray(rayOrigin, rayDirection);
}

Color RayTracer::rayTrace(Ray ray, int depth)
{
	Vector3D collisionPoint;
	Sphere* collidedObject = getClosestIntersection(ray, collisionPoint);

	if (collidedObject == nullptr)
	{
		return backgroundColor;
	}

	Color colorAtThisPoint = getColorWithLight(collidedObject, collisionPoint);

	if (depth >= maxDepth)
	{
		return colorAtThisPoint;
	}

	/*Ray reflected = getReflectedRay();
	Color reflectedColor = rayTrace(reflected, depth + 1);
	colorAtThisPoint = colorAtThisPoint.add(reflectedColor);

	Ray refracted = getRefractedRay();
	Color refractedColor = rayTrace(refracted, depth + 1);
	colorAtThisPoint = colorAtThisPoint.add(reflectedColor);
*/
	return colorAtThisPoint;
}

Sphere* RayTracer::getClosestIntersection(Ray ray, Vector3D& intersectionPoint)
{
	double closestIntersection = 1000000000;
	Sphere* intersectedObject = nullptr;

	for (int i = 0; i < sceneObjects.size(); i++)
	{
		IntersectionPoint point;
		bool intersected = sceneObjects[i].getClosestIntersection(ray, point);

		if (intersected && point.distance < closestIntersection)
		{
			intersectedObject = &sceneObjects[i];
			closestIntersection = point.distance;
		}
	}

	return intersectedObject;
}

Color RayTracer::getColorWithLight(Sphere* object, Vector3D pointOnObject)
{
	return object->color;
}