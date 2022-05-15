#pragma once
#include "Surface.h"
#include "Ray.h"
#include "Material.h"

class Triangle : public Surface {
private:
	glm::vec3 aVertex;
	glm::vec3 bVertex;
	glm::vec3 cVertex;
public:
	Triangle(glm::vec3 aVert, glm::vec3 bVert, glm::vec3 cVert, const std::shared_ptr<Material>& mat);
	bool IsHit(Ray ray, float t0, float t1, HitData& record);
	glm::vec3 Color(HitData& hitData, WorldState& world);
	glm::vec3 GetSurfaceNormal(HitData& hitData);
	glm::vec3 GetUnitSurfaceNormal(HitData& hitData);
	glm::vec3 GetIntersectionPoint(HitData& hitData);
};