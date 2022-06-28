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

// Generates the raytraced image
class RayTracer {
private:
	WorldState world;
	// Calculates an individual picture on the image, updates the iamge data
	void calculatePixel(int xPixel, int yPixel);
	// Calculates rows [startRow, endRow) on the pixel, updates the image data
	void calculateRows(int startRow, int endRow);
	// Calculates a single row, updates the image data
	void calculateRow(int row);
	// Calculates a single column, updates the image data
	void calculateColumn(int col);
public:
	RTImage image;
	RayTracer(WorldState world);
	RayTracer();
	bool Render();
	// Gets the image data
	const std::vector<glm::vec3>& getPixels();
	int getWidth();
	int getHeight();
	// Updates the size of the image, resets the image data
	bool refreshImage(int newWidth, int newHeight);
	// Updates the world state used by the ray tracer, resets the image
	bool setWorld(const WorldState& newWorld);
};