#pragma once
#include "Material.h"
#include "WorldState.h"

class Lambertian : public Material {
private:
	glm::vec3 diffuseCoeff;
public:
	Lambertian(glm::vec3 diffuseCoeff);
	glm::vec3 Shading(HitData& hitData, WorldState& world);
};