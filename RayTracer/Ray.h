#pragma once
#include <glm/glm.hpp>

// Ray pointing from an origin to a direction
class Ray {
public:
	glm::vec3 origin;
	glm::vec3 dir;
	Ray();
	// Used for general rays
	Ray(const glm::vec3& origin, const glm::vec3& dir);
	// Used for projection rays
	Ray(const glm::vec3& origin, const glm::vec3& dir, float u, float v, float focalLength);
};	