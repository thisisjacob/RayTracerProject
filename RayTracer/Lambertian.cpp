#include "Lambertian.h"
#include "MathFunctions.h"

Lambertian::Lambertian(glm::vec3 diffuseCoeff) {
	this->diffuseCoeff = glm::vec3(diffuseCoeff);
}

glm::vec3 Lambertian::Shading(HitData& hitData, WorldState& world) {
	glm::vec3 unitNormal = hitData.HitSurface.get()->GetSurfaceNormal(hitData);
	double lightCalc = 0.0;
	for (auto light : world.GetLights()) {
		glm::vec3 lVecUnit = light.get()->lightPos - hitData.HitSurface.get()->GetIntersectionPoint(hitData);
		lVecUnit /= lVecUnit.length();
		lightCalc += light.get()->intensity * std::max(0.0f, glm::dot(unitNormal, lVecUnit));
	}
	if (lightCalc > 0.0) {

	}
	return glm::vec3(Clamp(diffuseCoeff.x * lightCalc, 0.0, 1.0), Clamp(diffuseCoeff.y * lightCalc, 0.0, 1.0), Clamp(diffuseCoeff.z * lightCalc, 0.0, 1.0));
}


/*
class Lambertian : public Material {
public:
	Lambertian(glm::vec3 diffuseCoeff, glm::vec3 lightPos);
	glm::vec3 Shading(HitData& hitData);
};
*/