#pragma once
#include "Material.h"

class BlinnPhong : Material {
private:
	glm::tvec3<double> diffuseCoeff;
	glm::tvec3<double> specularCoeff;
	double phongExponent;
public:
	BlinnPhong(glm::tvec3<double> diffuseCoeff, glm::tvec3<double> specularCoeff, double phongExponent);
	glm::tvec3<double> Shading(HitData& hitData, WorldState& world);
};
