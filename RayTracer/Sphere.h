#pragma once
#include "Surface.h"
#include "Ray.h"
#include "Material.h"

class Sphere : public Surface {
private:
	double r;
	glm::tvec3<double> center;
	std::shared_ptr<Material> mat;
public:
	Sphere(double u, double v, double w, double r, Material* mat);
	bool IsHit(Ray ray, double t0, double t1, HitData& record);
	glm::tvec3<double> Color(HitData& hitData, WorldState& world);
	glm::tvec3<double> GetSurfaceNormal(HitData& hitData);
	glm::tvec3<double> GetIntersectionPoint(HitData& hitData);
};