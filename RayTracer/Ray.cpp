#include "Ray.h"

Ray::Ray() {
	origin = glm::vec3();
	dir = glm::vec3();
}

Ray::Ray(glm::vec3 origin, int focalLength, int u, int v) {
	origin = glm::vec3(origin);
	dir = glm::vec3(-focalLength, u, v);
}