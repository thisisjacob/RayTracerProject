#pragma once
#include "Sphere.h"

Sphere::Sphere(float w, float u, float v, float r) {
	center = glm::vec3(u, v, w);
	this->r = r;
}

bool Sphere::IsHit(Ray ray, float t0, float t1, HitData& record) {
	glm::vec3 eMinusc = ray.origin - center;

	// Use quadratic formula to test discriminant for intersections
	double A = glm::dot(ray.dir, ray.dir);
	double B = 2.0 * ((double)glm::dot(ray.dir, eMinusc));
	double C = glm::dot(eMinusc, eMinusc) - (r * r);
	double discriminant = B * B - 4.0 * A * C;
	if (discriminant < 0) return false;

	double addT = (-B + sqrt(discriminant)) / (2 * A);
	double minusT = (-B - sqrt(discriminant)) / (2 * A);

	// MinusT is always the smaller T, socheck it first
	if (minusT > t0 && minusT < t1) {
		record.T = minusT;
		record.IsHit = true;
		return true;
	}
	else if (addT > t0 && addT < t1) {
		record.T = addT;
		record.IsHit = true;
		return true;
	}

	return false;
}