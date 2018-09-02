#include "pch.h"
#include "RayTracer.h"
#include "Bitmap.h"

const Color RayTracer::backgroundColor = Color(88, 77, 70);
const int RayTracer::maxDepth = 1;

RayTracer::RayTracer()
{
	sceneObjects.push_back(Sphere(Vector3D(1, 1, 1), 1));
	sceneObjects.push_back(Sphere(Vector3D(4, 0, 0), .5));
	lightSources.push_back(Vector3D(0, .5, 3));
}

void RayTracer::renderPicture(int imageWidth, int imageHeight, char* filename) 
{
	Bitmap bitmap(imageWidth, imageHeight);

	for (int x = 0; x < imageWidth; x++)
	{
		for (int y = 0; y < imageHeight; y++) 
		{
			Color thisColor = renderPixel(x, y);
			bitmap.setPixel(x, y, thisColor);
		}
	}

	bitmap.writeToFile(filename);
}

Color RayTracer::renderPixel(int x, int y)
{
	Ray ray = getRayForPixel(x, y);
	Color c = rayTrace(ray, 0);
}

Ray RayTracer::getRayForPixel(int x, int y)
{
	TODO 
}

Color RayTracer::rayTrace(Ray ray, int depth)
{
	Vector3D collisionPoint;
	Sphere* collidedObject = getClosestIntersection(ray, collisionPoint);

	if (!collidedObject)
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
	Sphere* intersectedObject;

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