#include "IdealSpecular.h"

IdealSpecular::IdealSpecular() {
	ambientCoeff = glm::tvec3<double>();
	ambientIntensity = glm::tvec3<double>();
	diffuseCoeff = glm::tvec3<double>();
	specularCoeff = glm::tvec3<double>();
	phongExponent = 0.0;
}

glm::tvec3<double> IdealSpecular::Shading(HitData& hitData, WorldState& world) {
	glm::tvec3<double> norm = hitData.HitSurface->GetUnitSurfaceNormal(hitData);
	glm::tvec3<double> d = hitData.IntersectingRay.dir;
	glm::tvec3<double> r = d - 2 * (glm::dot(d, norm)) * norm;
	glm::tvec3<double> lightCalc = glm::tvec3<double>(0.0);
	lightCalc += 0.0;
	return glm::tvec3<double>(Clamp(lightCalc.x, 0.0, 1.0), Clamp(lightCalc.y, 0.0, 1.0), Clamp(lightCalc.z, 0.0, 1.0));
}

bool IdealSpecular::SetAmbientCoeff(glm::tvec3<double> newAmbient) {
	ambientCoeff = newAmbient;
	return true;
}

bool IdealSpecular::SetAmbientIntensity(glm::tvec3<double> newIntensity) {
	ambientIntensity = newIntensity;
	return true;
}

bool IdealSpecular::SetDiffuseCoeff(glm::tvec3<double> newDiffuse) {
	diffuseCoeff = newDiffuse;
	return true;
}

bool IdealSpecular::SetSpecularCoeff(glm::tvec3<double> newSpecular) {
	specularCoeff = newSpecular;
	return true;
}

bool IdealSpecular::SetPhongExponent(double exponent) {
	phongExponent = exponent;
	return true;
}