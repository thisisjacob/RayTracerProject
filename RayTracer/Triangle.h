#pragma once
#include "Surface.h"
#include "Ray.h"
#include "Material.h"

class Triangle : public Surface {
private:
	glm::tvec3<double> aVertex;
	glm::tvec3<double> bVertex;
	glm::tvec3<double> cVertex;
public:
	Triangle(glm::tvec3<double> aVert, glm::tvec3<double> bVert, glm::tvec3<double> cVert, const std::shared_ptr<Material>& mat);
	bool IsHit(Ray ray, double t0, double t1, HitData& record);
	glm::tvec3<double> Color(HitData& hitData, WorldState& world);
	glm::tvec3<double> GetSurfaceNormal(HitData& hitData);
	glm::tvec3<double> GetUnitSurfaceNormal(HitData& hitData);
	glm::tvec3<double> GetIntersectionPoint(HitData& hitData);
};