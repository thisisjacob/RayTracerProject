#pragma once
#include <glm/glm.hpp>
#include "Ray.h"

class Ray {
public:
	glm::tvec3<double> origin;
	glm::tvec3<double> dir;
	Ray();
	Ray(glm::tvec3<double> origin, double focalLength, double u, double v);
};