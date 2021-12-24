#include "Lambertian.h"

Lambertian::Lambertian(glm::vec3 diffuseCoeff, glm::vec3 lightPos) {
	this->diffuseCoeff = glm::vec3(diffuseCoeff);
	this->lightPos = glm::vec3(lightPos);
}

glm::vec3 Lambertian::Shading(HitData& hitData) {
	glm::vec3 unitNormal = hitData.HitSurface.get()->GetSurfaceNormal(hitData);
	glm::vec3 lVecUnit = lightPos - hitData.HitSurface.get()->GetIntersectionPoint(hitData);
	lVecUnit /= lVecUnit.length();
	// TODO: Replace constant with intensity
	double lightCalc = 5.0 * std::max(0.0f, glm::dot(unitNormal, lVecUnit));
	return glm::vec3(diffuseCoeff.x * lightCalc, diffuseCoeff.y * lightCalc, diffuseCoeff.z * lightCalc);
}


/*
class Lambertian : public Material {
public:
	Lambertian(glm::vec3 diffuseCoeff, glm::vec3 lightPos);
	glm::vec3 Shading(HitData& hitData);
};
*/