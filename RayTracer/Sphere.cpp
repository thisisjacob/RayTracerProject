#pragma once
#include "Sphere.h"

Sphere::Sphere(float w, float u, float v, float r) {
	center = glm::vec3(w, u, v);
	this->r = r;
}

bool Sphere::IsHit(Ray ray, float t0, float t1, HitData& record) {
	glm::vec3 eMinusc = ray.origin - center;

	// Use quadratic formula to test discriminant for intersections
	double A = glm::dot(ray.dir, ray.dir);
	double B = 2.0 * ((double)glm::dot(ray.dir, eMinusc));
	double C = glm::dot(eMinusc, eMinusc) - pow(r, 2.0);
	double discriminant = pow(B, 2.0) - 4.0 * A * C;
	if (discriminant < 0) return false;
	
	double root = sqrt(pow(glm::dot(ray.dir, eMinusc), 2.0) * A * C);

	double addT = (glm::dot(-ray.dir, eMinusc) + root) / A;
	double minusT = (glm::dot(-ray.dir, eMinusc) - root) / A;

	// TODO: Find which of these is smaller
	if (addT > t0 && addT < t1) {
		record.T = addT;
		record.IsHit = true;
		return true;
	}
	else if (minusT > t0 && minusT < t1) {
		record.T = minusT;
		record.IsHit = true;
		return true;
	}

	return false;
}