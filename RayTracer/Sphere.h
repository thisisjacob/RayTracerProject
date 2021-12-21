#pragma once
#include "Surface.h"
#include "Ray.h"

class Sphere : public Surface {
private:
	float r;
	glm::vec3 center;
public:
	Sphere(float u, float v, float w, float r);
	bool IsHit(Ray ray, float t0, float t1, HitData& record);
};