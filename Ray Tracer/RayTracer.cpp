#include "pch.h"
#include "RayTracer.h"
#include "Bitmap.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>

const Color RayTracer::backgroundColor = Color(2, 2, 2);
const int RayTracer::maxDepth = 1;

RayTracer::RayTracer()
{
	sceneObjects.push_back(Sphere(Vector3D(-5, 5, -5), 1, Color(250, 200, 200)));
	sceneObjects.push_back(Sphere(Vector3D(-5, 0, -5), 1, Color(250, 250, 200)));
	sceneObjects.push_back(Sphere(Vector3D(-3, 1.5, -5), .2, Color(100, 250, 200)));
	sceneObjects.push_back(Sphere(Vector3D(0, 0, -5), 1, Color(200, 250, 200)));
	lightSources.push_back(Vector3D(1, 5, -5));
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
	return traceRay(ray, 0);
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

Color RayTracer::traceRay(Ray ray, int depth)
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
		Vector3D point;
		double intersectionDistance;
		bool intersected = sceneObjects[i].getClosestIntersection(ray, point, intersectionDistance);

		if (intersected && intersectionDistance < closestIntersection)
		{
			intersectedObject = &sceneObjects[i];
			closestIntersection = intersectionDistance;
			intersectionPoint = point;
		}
	}

	return intersectedObject;
}

Color RayTracer::getColorWithLight(Sphere* object, Vector3D pointOnObject)
{
	// todo check this https://stackoverflow.com/questions/33054399/raytracing-lighting-equations

	bool enableAmbientLight = true;
	bool enableDiffuseLight = true;

	Color colorAtPoint(0, 0, 0);

	if (enableAmbientLight)
	{
		double ambientCoefficient = 0.1;
		colorAtPoint += getAmbientLight(object) * ambientCoefficient;
	}

	if (enableDiffuseLight)
	{
		double diffuseCoefficient = 1;
		colorAtPoint += getDiffuseLight(object, pointOnObject) * diffuseCoefficient;
	}

	return colorAtPoint;
}

Color RayTracer::getAmbientLight(Sphere* object)
{
	return object->color;
}

Color RayTracer::getDiffuseLight(Sphere* object, Vector3D pointOnObject)
{
	// Diffuse lighting (aka "lambertian")
	Vector3D normal = object->getNormal(pointOnObject);
	Vector3D lightDirection = (lightSources[0] - pointOnObject).normalized(); // direction from point towards light

	Segment3D betweenLightAndObject(Ray(lightSources[0], lightDirection * -1), (lightSources[0] - pointOnObject).getLength());

	if (anyOtherObjectsIntersectSegment(betweenLightAndObject, object))
	{
		return Color(0, 0, 0);
	}

	double val = std::max(normal.dot(lightDirection), 0.0);
	double intensity = 1; // todo: this would be an attribute of the light 
	// todo: change intensity based on distance

	int r = object->color.r * val * intensity;
	int g = object->color.g * val * intensity;
	int b = object->color.b * val * intensity;
	
	Color(r, g, b);
}

bool RayTracer::anyOtherObjectsIntersectSegment(Segment3D segment, Sphere* objectToExclude)
{
	for (Sphere & sceneObject : sceneObjects) 
	{
		if (sceneObject == *objectToExclude) 
		{
			continue;
		}

		if (sceneObject.intersects(segment))
		{
			return true;
		}
	}

	return false;
}