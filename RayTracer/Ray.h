#pragma once
#include <glm/glm.hpp>
#include "Ray.h"

class WorldState;

class Ray {
public:
	glm::vec3 origin;
	glm::vec3 dir;
	Ray();
	Ray(glm::vec3 origin, float focalLength, float u, float v);
	Ray(const glm::vec3& origin, const glm::vec3& dir);
};	