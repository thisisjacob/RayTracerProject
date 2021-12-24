#pragma once
#include "Material.h"

class Lambertian : public Material {
private:
	glm::vec3 diffuseCoeff;
	glm::vec3 lightPos;
public:
	Lambertian(glm::vec3 diffuseCoeff, glm::vec3 lightPos);
	glm::vec3 Shading(HitData& hitData);
};