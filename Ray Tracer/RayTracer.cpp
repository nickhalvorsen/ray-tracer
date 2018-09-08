#include "pch.h"
#include "RayTracer.h"
#include "Bitmap.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Quad.h"
#include "MathUtility.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>
#include <memory>

RayTracer::RayTracer() : RayTracer(0, 2, Color(0, 0, 0)) { }

RayTracer::RayTracer(int antiAliasingFactor, int maxDepth, Color backgroundColor)
{
	_antiAliasingFactor = antiAliasingFactor;
	_maxDepth = maxDepth;
	_backgroundColor = backgroundColor;

	_sceneObjects.push_back(std::shared_ptr<SceneObject>(new Sphere(1, Vector3D(-5, 5, -5), 1, Color(250, 200, 200), 0)));
	_sceneObjects.push_back(std::shared_ptr<SceneObject>(new Sphere(2, Vector3D(-5, 0, -5), 1, Color(250, 250, 200), 0)));
	_sceneObjects.push_back(std::shared_ptr<SceneObject>(new Sphere(3, Vector3D(-3, 1.5, -5), .2, Color(100, 250, 200), 0)));
	_sceneObjects.push_back(std::shared_ptr<SceneObject>(new Sphere(4, Vector3D(0, 0, -5), 1, Color(255, 255, 255), .4)));
	_sceneObjects.push_back(std::shared_ptr<SceneObject>(new Triangle(5, Vector3D(4, -1, -6), Vector3D(2, -2, -4), Vector3D(2, -1, -6), Color(200, 200, 250), 0)));
	_sceneObjects.push_back(std::shared_ptr<SceneObject>(new Quad(5, Vector3D(-5, -1, 5), Vector3D(-5, -1, -5), Vector3D(5, -1, -5), Vector3D(5, -1, 5), Color(200, 177, 12), 0)));

	_lightSources.push_back(LightSource(Vector3D(1, 5, -5), Color(255, 255, 255)));
}

Color RayTracer::renderPixel(int imageWidth, int imageHeight, int x, int y)
{
	if (_antiAliasingFactor > 1)
	{
		return renderPixelWithAntiAliasing(imageWidth, imageHeight, x, y);
	}

	Ray ray = getRayForPixel(imageWidth, imageHeight, x, y);
	return traceRay(ray, 0);
}

Color RayTracer::renderPixelWithAntiAliasing(int imageWidth, int imageHeight, int x, int y) 
{
	std::vector<Color> samples;

	// get the anti-aliasing ray by pretending the image has more pixels
	int extraPixelsPerPixel = _antiAliasingFactor * _antiAliasingFactor;
	for (int i = 0; i < extraPixelsPerPixel; i++)
	{
		int testWidth = imageWidth * _antiAliasingFactor;
		int testHeight = imageHeight * _antiAliasingFactor;
		int testX = x * _antiAliasingFactor + (i %_antiAliasingFactor);
		int testY = y * _antiAliasingFactor + i / _antiAliasingFactor;
		Ray ray = getRayForPixel(testWidth, testHeight, testX, testY);
		samples.push_back(traceRay(ray, 0));
	}

	return averageColor(samples);
}

Color RayTracer::averageColor(const std::vector<Color>& samples)
{
	int totalR = 0;
	int totalG = 0;
	int totalB = 0;

	for (int i = 0; i < samples.size(); i++)
	{
		totalR += samples[i].r;
		totalG += samples[i].g;
		totalB += samples[i].b;
	}

	// We can assume that there is at least 1 sample per pixel. 
	float averageR = totalR / samples.size();
	float averageG = totalG / samples.size();
	float averageB = totalB / samples.size();

	return Color(averageR, averageG, averageB);
}

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

	std::shared_ptr<SceneObject> collidedObject = getClosestIntersection(ray, collisionPoint);

	if (collidedObject == nullptr)
	{
		return _backgroundColor;
	}

	Color colorAtThisPoint = getColorWithLight(collidedObject, collisionPoint);

	if (depth >= _maxDepth)
	{
		return colorAtThisPoint;
	}

	if (collidedObject->getReflectionIndex() > 0)
	{
		Ray reflected = getReflectedRay(ray, collidedObject, collisionPoint);
		Color reflectedColor = traceRay(reflected, depth + 1);

		float reflectedLightRatio = 1 - calculateReflectedLight(
			ray.getDirection()
			, collidedObject->getNormal(reflected.origin)
			, collidedObject->getReflectionIndex());

		Color objectColorPortion = (colorAtThisPoint * (1 - reflectedLightRatio));
		Color reflectedColorPortion = (reflectedColor * (reflectedLightRatio));

		colorAtThisPoint = objectColorPortion + reflectedColorPortion;
	}
	/*
	Ray refracted = getRefractedRay();
	Color refractedColor = rayTrace(refracted, depth + 1);
	colorAtThisPoint = colorAtThisPoint.add(reflectedColor);
	*/
	return colorAtThisPoint;
}

std::shared_ptr<SceneObject> RayTracer::getClosestIntersection(Ray ray, Vector3D& intersectionPoint)
{
	double closestIntersection = 1000000000;
	std::shared_ptr<SceneObject> intersectedObject = nullptr;

	for (int i = 0; i < _sceneObjects.size(); i++)
	{
		Vector3D point;
		double intersectionDistance;
		bool intersected = _sceneObjects[i]->getClosestIntersection(ray, point, intersectionDistance);

		if (intersected && intersectionDistance < closestIntersection)
		{ 
			intersectedObject = _sceneObjects[i];
			closestIntersection = intersectionDistance;
			intersectionPoint = point;
		}
	}

	return intersectedObject;
}

Color RayTracer::getColorWithLight(const std::shared_ptr<SceneObject>& object, Vector3D pointOnObject)
{
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
		colorAtPoint += getAllDiffuseLight(object, pointOnObject) * diffuseCoefficient;
	}

	return colorAtPoint;
}

Color RayTracer::getAmbientLight(const std::shared_ptr<SceneObject>& object)
{
	return object->color;
}

// Diffuse lighting (aka "lambertian")
Color RayTracer::getAllDiffuseLight(const std::shared_ptr<SceneObject>& object, Vector3D pointOnObject)
{
	Color colorAtPoint(0, 0, 0);

	for (int i = 0; i < _lightSources.size(); i++)
	{
		colorAtPoint += getDiffuseLight(object, pointOnObject, _lightSources[i]);
	}

	return colorAtPoint;
}

Color RayTracer::getDiffuseLight(const std::shared_ptr<SceneObject>& object, Vector3D pointOnObject, LightSource lightSource)
{
	Vector3D normal = object->getNormal(pointOnObject);
	Vector3D pointToLight = (_lightSources[0].point - pointOnObject).normalized();

	Segment3D betweenLightAndObject(Ray(lightSource.point, pointToLight * -1), (lightSource.point - pointOnObject).getLength());

	if (anyOtherObjectsIntersectSegment(betweenLightAndObject, object))
	{
		return Color(0, 0, 0);
	}

	double val = std::max(normal.dot(pointToLight), 0.0);
	// todo: change intensity based on distance

	int r = object->color.r * val * (lightSource.intensity.r / 255.0);
	int g = object->color.g * val * (lightSource.intensity.g / 255.0);
	int b = object->color.b * val * (lightSource.intensity.b / 255.0);

	Color(r, g, b);
}

bool RayTracer::anyOtherObjectsIntersectSegment(Segment3D segment, std::shared_ptr<SceneObject> objectToExclude)
{
	for (std::shared_ptr<SceneObject> sceneObject : _sceneObjects)
	{
		if (sceneObject->getId() == objectToExclude->getId()) 
		{
			continue;
		}

		if (sceneObject->intersects(segment))
		{
			return true;
		}
	}

	return false;
}

Ray RayTracer::getReflectedRay(Ray ray, const std::shared_ptr<SceneObject>& object, Vector3D objectCollisionPoint)
{
	Vector3D direction = ray.getDirection().normalized();
	Vector3D normal = object->getNormal(objectCollisionPoint);
	Vector3D reflectedDirection = direction - normal * (2 * direction.dot(normal));
	Vector3D reflectionStartPoint = objectCollisionPoint + (reflectedDirection.normalized() * 0.0000001);
	return Ray(reflectionStartPoint, reflectedDirection.normalized());
}

// aka "fresnel equation"
float RayTracer::calculateReflectedLight(const Vector3D lightDirection, const Vector3D normalDirection, const float objectReflectionIndex)
{
	float cosi = MathUtility::clamp(-1, 1, lightDirection.dot(normalDirection));
	float etai = 1, etat = objectReflectionIndex;
	if (cosi > 0) { std::swap(etai, etat); }
	// Compute sini using Snell's law
	float sint = etai / etat * sqrtf(std::max(0.f, 1 - cosi * cosi));
	// Total internal reflection
	if (sint >= 1) {
		return 1;
	}
	else {
		float cost = sqrtf(std::max(0.f, 1 - sint * sint));
		cosi = fabsf(cosi);
		float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
		float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
		return (Rs * Rs + Rp * Rp) / 2;
	}
	// As a consequence of the conservation of energy, transmittance is given by:
	// kt = 1 - kr;
}