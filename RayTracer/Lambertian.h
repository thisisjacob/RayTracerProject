#pragma once
#include "Material.h"

class Lambertian : public Material {
private:
	glm::tvec3<double> diffuseCoeff;
public:
	Lambertian(glm::tvec3<double> diffuseCoeff);
	glm::tvec3<double> Shading(HitData& hitData, WorldState& world);
};