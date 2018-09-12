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
	Color getColorWithLight(SceneObject* object, const Vector3D& pointOnObject);
	Color getAmbientLight(SceneObject* object);
	Color getAllDiffuseLight(SceneObject* object, const Vector3D& pointOnObject);
	Color getDiffuseLight(SceneObject* object, const Vector3D& pointOnObject, const LightSource& lightSource);
	bool anyOtherObjectsIntersectSegment(Segment3D segment, SceneObject* objectToExclude);
	Color getReflectedColor(Ray ray, SceneObject* collidedObject, const Vector3D& collisionPoint, int depth, double& reflectedLightRatio);
	Ray getReflectedRay(Ray ray, SceneObject* object, Vector3D objectCollisionPoint);
	double calculateReflectedLight(const Vector3D& lightDirection, const Vector3D& normalDirection, const double objectReflectionIndex);
	Color averageColor(const std::vector<Color>& samples);
};