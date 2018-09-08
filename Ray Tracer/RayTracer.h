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
	RayTracer();
	RayTracer(int antiAliasingFactor, int maxDepth, Color backgroundColor);
	Color renderPixel(int imageWidth, int imageHeight, int x, int y);
private:
	Color _backgroundColor;
	int _maxDepth;
	int _antiAliasingFactor;
	std::vector< std::shared_ptr<SceneObject> > _sceneObjects;
	std::vector<LightSource> _lightSources;
	Color renderPixelWithAntiAliasing(int imageWidth, int imageHeight, int x, int y);
	Ray getRayForPixel(int imageWidth, int imageHeight, int x, int y);
	Color traceRay(Ray ray, int depth);
	std::shared_ptr<SceneObject> getClosestIntersection(Ray ray, Vector3D& collisionPoint);
	Color getColorWithLight(const std::shared_ptr<SceneObject>& object, Vector3D pointOnObject);
	Color getAmbientLight(const std::shared_ptr<SceneObject>& object);
	Color getAllDiffuseLight(const std::shared_ptr<SceneObject>& object, Vector3D pointOnObject);
	Color getDiffuseLight(const std::shared_ptr<SceneObject>& object, Vector3D pointOnObject, LightSource lightSource);
	bool anyOtherObjectsIntersectSegment(Segment3D segment, std::shared_ptr<SceneObject> objectToExclude);
	Ray getReflectedRay(Ray ray, const std::shared_ptr<SceneObject>& object, Vector3D objectCollisionPoint);
	float calculateReflectedLight(const Vector3D lightDirection, const Vector3D normalDirection, const float objectReflectionIndex);
	Color averageColor(const std::vector<Color>& samples);
};