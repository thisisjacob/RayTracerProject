#pragma once
#include "Material.h"
#include "MathFunctions.h"

const int MAX_REFLECTION_RECURSION_DEPTH = 5;

class IdealSpecular : public Material {
private:
	glm::tvec3<double> ambientCoeff;
	glm::tvec3<double> ambientIntensity;
	glm::tvec3<double> diffuseCoeff;
	glm::tvec3<double> specularCoeff;
	double phongExponent;
public:
	IdealSpecular();
	glm::tvec3<double> Shading(HitData& hitData, WorldState& world);
	glm::tvec3<double> RecursiveShading(Ray ray, WorldState& world, int currIter);
	bool SetAmbientCoeff(glm::tvec3<double> newAmbient);
	bool SetAmbientIntensity(glm::tvec3<double> newIntensity);
	bool SetDiffuseCoeff(glm::tvec3<double> newDiffuse);
	bool SetSpecularCoeff(glm::tvec3<double> newSpecular);
	bool SetPhongExponent(double exponent);
};