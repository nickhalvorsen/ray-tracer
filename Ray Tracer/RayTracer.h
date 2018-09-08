#pragma once

#include <vector>
#include <memory>
#include "SceneObject.h"
#include "Ray.h"
#include "Segment3D.h"
#include "LightSource.h"


class RayTracer
{
public:
	RayTracer(int antiAliasingFactor, int maxDepth, std::vector<SceneObject*> sceneObjects, std::vector<LightSource> lightSources);
	Color renderPixel(int imageWidth, int imageHeight, int x, int y);
private:
	static const Color _backgroundColor;
	int _maxDepth;
	int _antiAliasingFactor;
	std::vector<SceneObject*> _sceneObjects;
	std::vector<LightSource> _lightSources;
	Color renderPixelWithAntiAliasing(int imageWidth, int imageHeight, int x, int y);
	Ray getRayForPixel(int imageWidth, int imageHeight, int x, int y);
	Color traceRay(Ray ray, int depth);
	SceneObject* getClosestIntersection(Ray ray, Vector3D& collisionPoint);
	Color getColorWithLight(SceneObject* object, Vector3D pointOnObject);
	Color getAmbientLight(SceneObject* object);
	Color getAllDiffuseLight(SceneObject* object, Vector3D pointOnObject);
	Color getDiffuseLight(SceneObject* object, Vector3D pointOnObject, LightSource lightSource);
	bool anyOtherObjectsIntersectSegment(Segment3D segment, SceneObject* objectToExclude);
	Ray getReflectedRay(Ray ray, SceneObject* object, Vector3D objectCollisionPoint);
	float calculateReflectedLight(const Vector3D lightDirection, const Vector3D normalDirection, const float objectReflectionIndex);
	Color averageColor(const std::vector<Color>& samples);
};