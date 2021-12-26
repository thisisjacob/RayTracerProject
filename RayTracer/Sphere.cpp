#pragma once
#include "Sphere.h"

Sphere::Sphere(double u, double v, double w, double r, Material* mat) {
	center = glm::tvec3<double>(u, v, w);
	this->r = r;
	this->mat = std::shared_ptr<Material>(mat);
}

bool Sphere::IsHit(Ray ray, double t0, double t1, HitData& record) {
	glm::tvec3<double> eMinusc = ray.origin - center;

	// Use quadratic formula to test discriminant for intersections
	double A = glm::dot(ray.dir, ray.dir);
	double B = 2.0 * glm::dot(ray.dir, eMinusc);
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

glm::tvec3<double> Sphere::Color(HitData& hitData, WorldState& world) {
	return mat.get()->Shading(hitData, world);
}

glm::tvec3<double> Sphere::GetIntersectionPoint(HitData& hitData) {
	glm::tvec3<double> p = glm::tvec3<double>(hitData.IntersectingRay.dir);
	p *= hitData.T;
	p += hitData.IntersectingRay.origin;
	return p;
}

glm::tvec3<double> Sphere::GetSurfaceNormal(HitData& hitData) {
	glm::tvec3<double> p = GetIntersectionPoint(hitData) - center;
	p /= p.length();
	return p;
}