#pragma once
#include "Surface.h"
#include "Ray.h"
#include "Material.h"

class Sphere : public Surface {
private:
	double r;
	glm::tvec3<double> center;
public:
	Sphere(double u, double v, double w, double r, const std::shared_ptr<Material> &mat);
	bool IsHit(Ray ray, double t0, double t1, HitData& record);
	glm::tvec3<double> Color(HitData& hitData, WorldState& world);
	glm::tvec3<double> GetSurfaceNormal(HitData& hitData);
	glm::tvec3<double> GetUnitSurfaceNormal(HitData& hitData);
	glm::tvec3<double> GetIntersectionPoint(HitData& hitData);
};