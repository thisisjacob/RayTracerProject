#pragma once
#include <glm/glm.hpp>
#include "Ray.h"
#include <iostream>
#include <fstream>

class RayTracer {
private:
	int imageWidth;
	int imageHeight;
	int focalLength;
	glm::vec3 eye;
public:
	RayTracer(int imageWidth, int imageHeight, float u, float v, float w, float focalLength);
	bool Render();
};