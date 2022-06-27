#pragma once
#include "Surface.h"
#include "Ray.h"
#include <memory>

class Surface;

// Holds information on an intersection with an object
struct HitData {
	bool IsHit;
	float T;
	std::shared_ptr<Surface> HitSurface;
	Ray IntersectingRay;
};