#include "Lambertian.h"
#include "MathFunctions.h"

Lambertian::Lambertian(glm::tvec3<double> diffuseCoeff) {
	this->diffuseCoeff = glm::tvec3<double>(diffuseCoeff);
}

glm::tvec3<double> Lambertian::Shading(HitData& hitData, WorldState& world) {
	glm::tvec3<double> unitNormal = hitData.HitSurface.get()->GetSurfaceNormal(hitData);
	double lightCalc = 0.0;
	for (auto light : world.GetLights()) {
		glm::tvec3<double> lVecUnit = light.get()->lightPos - hitData.HitSurface.get()->GetIntersectionPoint(hitData);
		lVecUnit /= lVecUnit.length();
		lightCalc += light.get()->intensity * std::max(0.0, glm::dot(unitNormal, lVecUnit));
	}
	if (lightCalc > 0.0) {

	}
	return glm::tvec3<double>(Clamp(diffuseCoeff.x * lightCalc, 0.0, 1.0), Clamp(diffuseCoeff.y * lightCalc, 0.0, 1.0), Clamp(diffuseCoeff.z * lightCalc, 0.0, 1.0));
}


/*
class Lambertian : public Material {
public:
	Lambertian(glm::tvec3<double> diffuseCoeff, glm::tvec3<double> lightPos);
	glm::tvec3<double> Shading(HitData& hitData);
};
*/