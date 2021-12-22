#pragma once
#include <glm/glm.hpp>
#include "Ray.h"
#include <iostream>
#include <fstream>
#include "Surface.h"
#include <vector>
#include "Sphere.h"

class RayTracer {
private:
	int imageWidth;
	int imageHeight;
	int focalLength;
	glm::vec3 eye;
	std::vector<std::unique_ptr<Surface>> objects;
public:
	RayTracer(int imageWidth, int imageHeight, float u, float v, float w, float focalLength);
	bool Render();
};