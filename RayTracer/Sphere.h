#pragma once
#include "Surface.h"
#include "Ray.h"
#include "Material.h"

class Sphere : public Surface {
private:
	float r;
	glm::vec3 center;
	std::shared_ptr<Material> mat;
public:
	Sphere(float u, float v, float w, float r, Material* mat);
	bool IsHit(Ray ray, float t0, float t1, HitData& record);
	glm::vec3 Color(HitData& hitData, WorldState& world);
	glm::vec3 GetSurfaceNormal(HitData& hitData);
	glm::vec3 GetIntersectionPoint(HitData& hitData);
};