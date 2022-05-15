#pragma once
#include <glm/glm.hpp>
#include "Ray.h"

class WorldState;

class Ray {
public:
	glm::tvec3<double> origin;
	glm::tvec3<double> dir;
	Ray();
	Ray(glm::tvec3<double> origin, double focalLength, double u, double v);
	Ray(const glm::tvec3<double> &origin, const glm::tvec3<double> &dir);
};