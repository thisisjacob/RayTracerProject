#pragma once
#include "Surface.h"
#include "Ray.h"
#include "Material.h"
#include "BoundingBox.h"

class Sphere : public Surface {
private:
	float r;
	glm::vec3 center;
public:
	Sphere(float u, float v, float w, float r, const std::shared_ptr<Material> &mat);
	HitData IsHit(const std::shared_ptr<Surface>& callingSurface, Ray ray, float t0, float t1, const HitData& record);
	BoundingBox boundingBox() const;
	glm::vec3 Color(HitData& hitData, WorldState& world, int currRecurrDepth = 0);
	glm::vec3 GetSurfaceNormal(HitData& hitData);
	glm::vec3 GetUnitSurfaceNormal(HitData& hitData);
	glm::vec3 GetIntersectionPoint(HitData& hitData);
};