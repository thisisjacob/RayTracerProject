#pragma once
#include "Surface.h"
#include "Ray.h"
#include <memory>

class Surface;

struct HitData {
	bool IsHit;
	double T;
	std::shared_ptr<Surface> HitSurface;
	Ray IntersectingRay;
};