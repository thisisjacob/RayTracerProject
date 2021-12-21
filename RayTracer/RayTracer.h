#pragma once
#include <glm/glm.hpp>
#include "Ray.h"

class RayTracer {
private:
	int imageWidth;
	int imageHeight;
	int focalLength;
	glm::vec3 eye;
public:
	RayTracer(int imageWidth, int imageHeight, int u, int v, int focalLength);
	bool Render();
};