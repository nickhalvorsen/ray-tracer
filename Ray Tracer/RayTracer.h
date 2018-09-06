#pragma once

#include <vector>
#include <memory>
#include "SceneObject.h"
#include "Ray.h"
#include "Segment3D.h"


class RayTracer
{
public:
	RayTracer();
	void renderPicture(int imageWidth, int imageHeight, char* filename);
private:
	const static Color backgroundColor;
	const static int maxDepth;
	std::vector< std::shared_ptr<SceneObject> > sceneObjects;
	std::vector<Vector3D> lightSources;
	Color renderPixel(int imageWidth, int imageHeight, int x, int y);
	Ray getRayForPixel(int imageWidth, int imageHeight, int x, int y);
	Color traceRay(Ray ray, int depth);
	std::shared_ptr<SceneObject> getClosestIntersection(Ray ray, Vector3D& collisionPoint);
	Color getColorWithLight(const std::shared_ptr<SceneObject>& object, Vector3D pointOnObject);
	Color getAmbientLight(const std::shared_ptr<SceneObject>& object);
	Color getDiffuseLight(const std::shared_ptr<SceneObject>& object, Vector3D pointOnObject);
	bool anyOtherObjectsIntersectSegment(Segment3D segment, std::shared_ptr<SceneObject> objectToExclude);
};