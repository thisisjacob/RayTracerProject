#include "Ray.h"

Ray::Ray() {
	origin = glm::tvec3<double>();
	dir = glm::tvec3<double>();
}

Ray::Ray(glm::tvec3<double> origin, double u, double v, double w) {
	this->origin = glm::tvec3<double>(origin);
	dir = glm::tvec3<double>(u, v, w);
}

Ray::Ray(const glm::tvec3<double> &origin, const glm::tvec3<double> &dir) {
	this->origin = glm::tvec3<double>(origin);
	this->dir = glm::tvec3<double>(dir);
}