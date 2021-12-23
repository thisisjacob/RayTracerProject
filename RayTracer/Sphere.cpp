#pragma once
#include "Sphere.h"

Sphere::Sphere(float u, float v, float w, float r, Material* mat) {
	center = glm::vec3(u, v, w);
	this->r = r;
	this->mat = std::shared_ptr<Material>(mat);
}

bool Sphere::IsHit(Ray ray, float t0, float t1, HitData& record) {
	glm::vec3 eMinusc = ray.origin - center;

	// Use quadratic formula to test discriminant for intersections
	double A = glm::dot(ray.dir, ray.dir);
	double B = 2.0 * ((double)glm::dot(ray.dir, eMinusc));
	double C = glm::dot(eMinusc, eMinusc) - (r * r);
	double discriminant = B * B - 4.0 * A * C;
	if (discriminant < 0) return false;

	double addT = (-B + sqrt(discriminant)) / (2.0 * A);
	double minusT = (-B - sqrt(discriminant)) / (2.0 * A);

	// MinusT is always the smaller T, so check it first
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

glm::vec3 Sphere::Color(HitData& hitData) {
	return mat.get()->Shading(hitData);
}