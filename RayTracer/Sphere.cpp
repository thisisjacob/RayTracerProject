#pragma once
#include "Sphere.h"

using std::shared_ptr;
using glm::tvec3;
using glm::dot;

Sphere::Sphere(float u, float v, float w, float r, const shared_ptr<Material>& mat) {
	center = glm::vec3(u, v, w);
	this->r = r;
	this->mat = mat;
}

bool Sphere::IsHit(const std::shared_ptr<Surface>& callingSurface, Ray ray, float t0, float t1, HitData& record) {
	glm::vec3 eMinusc = ray.origin - center;

	// Use quadratic formula to test discriminant for intersections
	float A = dot(ray.dir, ray.dir);
	float B = 2.0 * dot(ray.dir, eMinusc);
	float C = dot(eMinusc, eMinusc) - (r * r);
	float discriminant = B * B - 4.0 * A * C;
	if (discriminant < 0) return false;

	float addT = (-B + sqrt(discriminant)) / (2.0 * A);
	float minusT = (-B - sqrt(discriminant)) / (2.0 * A);

	// MinusT is always the smaller T, so check it first
	if (minusT > t0 && minusT < t1) {
		record.T = minusT;
		record.IsHit = true;
		record.HitSurface = callingSurface;
		return true;
	}
	else if (addT > t0 && addT < t1) {
		record.T = addT;
		record.IsHit = true;
		record.HitSurface = callingSurface;
		return true;
	}
	return false;
}

BoundingBox Sphere::boundingBox() const {
	glm::vec3 min = center - glm::vec3(r, r, r);
	glm::vec3 max = center + glm::vec3(r, r, r);
	return BoundingBox(min, max);
}

glm::vec3 Sphere::Color(HitData& hitData, WorldState& world) {
	return mat.get()->Shading(hitData, world);
}

glm::vec3 Sphere::GetIntersectionPoint(HitData& hitData) {
	glm::vec3 p = glm::vec3(hitData.IntersectingRay.dir);
	p *= hitData.T;
	p += hitData.IntersectingRay.origin;
	return p;
}

glm::vec3 Sphere::GetUnitSurfaceNormal(HitData& hitData) {
	return normalize(GetSurfaceNormal(hitData));
}

glm::vec3 Sphere::GetSurfaceNormal(HitData& hitData) {
	return GetIntersectionPoint(hitData) - center;
}