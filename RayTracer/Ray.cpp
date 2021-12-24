#include "Ray.h"

Ray::Ray() {
	origin = glm::vec3();
	dir = glm::vec3();
}

Ray::Ray(glm::vec3 origin, double focalLength, double u, double v) {
	this->origin = glm::vec3(origin);
	dir = glm::vec3(u, v, focalLength);
}