#include "Ray.h"

Ray::Ray() {
	origin = glm::tvec3<double>();
	dir = glm::tvec3<double>();
}

Ray::Ray(glm::tvec3<double> origin, double focalLength, double u, double v) {
	this->origin = glm::tvec3<double>(origin);
	dir = glm::tvec3<double>(u, v, -focalLength);
}