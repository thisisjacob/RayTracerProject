#pragma once
#include <glm/glm.hpp>
#include "Ray.h"

class Ray {
public:
	glm::vec3 origin;
	glm::vec3 dir;
	Ray();
	Ray(glm::vec3 origin, int focalLength, int u, int v);
};