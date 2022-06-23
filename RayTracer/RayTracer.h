#pragma once
#include <glm/glm.hpp>
#include "Ray.h"
#include <iostream>
#include <fstream>
#include "Surface.h"
#include <vector>
#include "Sphere.h"
#include "Triangle.h"
#include "WorldState.h"
#include "Camera.h"
#include <thread>

class RayTracer {
private:
	WorldState world;
	std::vector<glm::vec3> pixels;
	void calculatePixel(int xPixel, int yPixel);
	void calculatePixels(int startYPixel, int endYPixel);
	void calculateRow(int row);
	void calculateColumn(int col);
public:
	RayTracer(WorldState world);
	bool Render();
	const std::vector<glm::vec3>& getPixels();
	int getWidth();
	int getHeight();
	// Updates the size of the image, resets the image data
	bool refreshImage(int newWidth, int newHeight);
};