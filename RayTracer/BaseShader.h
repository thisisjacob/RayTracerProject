#pragma once
#include "Material.h"
#include "MathFunctions.h"

class BlinnPhong : public Material {
private:
	glm::vec3 ambientCoeff;
	glm::vec3 ambientIntensity;
	glm::vec3 diffuseCoeff;
	glm::vec3 specularCoeff;
	float phongExponent;
public:
	BlinnPhong();
	glm::vec3 Shading(HitData& hitData, WorldState& world);
	bool SetAmbientCoeff(glm::vec3 newAmbient);
	bool SetAmbientIntensity(glm::vec3 newIntensity);
	bool SetDiffuseCoeff(glm::vec3 newDiffuse);
	bool SetSpecularCoeff(glm::vec3 newSpecular);
	bool SetPhongExponent(float exponent);
};
