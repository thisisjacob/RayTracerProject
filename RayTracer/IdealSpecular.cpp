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
	glm::tvec3<double> d = glm::normalize(hitData.IntersectingRay.dir);
	glm::tvec3<double> r = glm::normalize(d - 2 * (glm::dot(d, norm)) * norm);
	glm::tvec3<double> p = hitData.HitSurface->GetIntersectionPoint(hitData);
	auto lightCalc = RecursiveShading(Ray(p, -r.z, r.x, r.y), world, 0, 6);
	return glm::tvec3<double>(Clamp(lightCalc.x, 0.0, 1.0), Clamp(lightCalc.y, 0.0, 1.0), Clamp(lightCalc.z, 0.0, 1.0));
}

glm::tvec3<double> IdealSpecular::RecursiveShading(Ray ray, WorldState& world, int currIter, int maxIter) {
	HitData hit = world.GetIntersection(ray, 0.00000000001);
	glm::tvec3<double> color = glm::tvec3<double>(0.0);
	if (!hit.IsHit || currIter >= maxIter)
		return color;
	else
		color = hit.HitSurface->Color(hit, world);
	glm::tvec3<double> norm = hit.HitSurface->GetUnitSurfaceNormal(hit);
	glm::tvec3<double> d = glm::normalize(hit.IntersectingRay.dir);
	glm::tvec3<double> r = glm::normalize(d - 2 * (glm::dot(d, norm)) * norm);
	glm::tvec3<double> p = hit.HitSurface->GetIntersectionPoint(hit);
	return color + specularCoeff * RecursiveShading(Ray(p, -r.z, r.x, r.y), world, currIter + 1, maxIter);
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