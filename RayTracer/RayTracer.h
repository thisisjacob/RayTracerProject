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
#include "RTImage.h"

class RayTracer {
private:
	WorldState world;
	void calculatePixel(int xPixel, int yPixel);
	void calculatePixels(int startYPixel, int endYPixel);
	void calculateRow(int row);
	void calculateColumn(int col);
public:
	RTImage image;
	RayTracer(WorldState world);
	RayTracer();
	bool Render();
	const std::vector<glm::vec3>& getPixels();
	int getWidth();
	int getHeight();
	// Updates the size of the image, resets the image data
	bool refreshImage(int newWidth, int newHeight);
	// Updates the world state used by the ray tracer
	bool setWorld(const WorldState& newWorld);
};