#include "Ray.h"

Ray::Ray() {
	origin = glm::vec3();
	dir = glm::vec3();
}

Ray::Ray(glm::vec3 origin, float u, float v, float w) {
	this->origin = glm::vec3(origin);
	dir = glm::vec3(u, v, w);
}

Ray::Ray(const glm::vec3 &origin, const glm::vec3 &dir) {
	this->origin = glm::vec3(origin);
	this->dir = glm::vec3(dir);
}