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

class RayTracer {
private:
	WorldState world;
public:
	RayTracer(WorldState world);
	bool Render();
};