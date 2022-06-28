#include "Ray.h"

Ray::Ray() {
	origin = glm::vec3();
	dir = glm::vec3();
}

Ray::Ray(const glm::vec3 &origin, const glm::vec3 &dir) {
	this->origin = glm::vec3(origin);
	this->dir = glm::vec3(dir);
}

Ray::Ray(const glm::vec3& origin, const glm::vec3& dir, float u, float v, float focalLength) {
	this->origin = glm::vec3(origin);
	this->dir = glm::vec3((dir.x * focalLength) + u, (dir.y * focalLength) + v, dir.z * focalLength);
}