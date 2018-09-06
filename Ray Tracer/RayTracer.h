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
	Color renderPixel(int imageWidth, int imageHeight, int x, int y);
private:
	const static Color backgroundColor;
	const static int maxDepth;
	std::vector< std::shared_ptr<SceneObject> > sceneObjects;
	std::vector<LightSource> lightSources;
	Ray getRayForPixel(int imageWidth, int imageHeight, int x, int y);
	Color traceRay(Ray ray, int depth);
	std::shared_ptr<SceneObject> getClosestIntersection(Ray ray, Vector3D& collisionPoint);
	Color getColorWithLight(const std::shared_ptr<SceneObject>& object, Vector3D pointOnObject);
	Color getAmbientLight(const std::shared_ptr<SceneObject>& object);
	Color getAllDiffuseLight(const std::shared_ptr<SceneObject>& object, Vector3D pointOnObject);
	Color getDiffuseLight(const std::shared_ptr<SceneObject>& object, Vector3D pointOnObject, LightSource lightSource);
	bool anyOtherObjectsIntersectSegment(Segment3D segment, std::shared_ptr<SceneObject> objectToExclude);
};