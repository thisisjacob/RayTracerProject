#pragma once
#include <glm/glm.hpp>
#include "Ray.h"
#include <iostream>
#include <fstream>
#include "Surface.h"
#include <vector>
#include "Sphere.h"
#include "WorldState.h"

class RayTracer {
private:
	int imageWidth;
	int imageHeight;
	double focalLength;
	double aspectRatio;
	glm::tvec3<double> eye;
	WorldState world;
public:
	RayTracer(int imageWidth, int imageHeight, double u, double v, double w, double focalLength, WorldState world);
	bool Render();
};