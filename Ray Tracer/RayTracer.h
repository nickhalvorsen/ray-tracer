#pragma once

#include <vector>
#include "Sphere.h"
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
	std::vector<Sphere> sceneObjects;
	std::vector<Vector3D> lightSources;
	Color renderPixel(int imageWidth, int imageHeight, int x, int y);
	Ray getRayForPixel(int imageWidth, int imageHeight, int x, int y);
	Color rayTrace(Ray ray, int depth);
	Sphere* getClosestIntersection(Ray ray, Vector3D& collisionPoint);
	Color getColorWithLight(Sphere* object, Vector3D pointOnObject);
	bool anyOtherObjectsIntersectSegment(Segment3D segment, Sphere* objectToExclude);
};