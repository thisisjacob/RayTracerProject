#include "RefractionShader.h"

RefractionShader::RefractionShader(float refractiveIndex) {
	this->refractiveIndex = refractiveIndex;
}

glm::vec3 RefractionShader::Shading(HitData& hitRecord, WorldState& world, int currRecurDepth) {
	if (recursionLimitHit(currRecurDepth)) {
		return glm::vec3(0, 0, 0);
	}

	glm::vec3 r = reflectRay(hitRecord).dir;
	glm::vec3 d = glm::normalize(hitRecord.IntersectingRay.dir);
	glm::vec3 n = hitRecord.HitSurface->GetUnitSurfaceNormal(hitRecord);
	glm::vec3 t;
	glm::vec3 p = hitRecord.HitSurface->GetIntersectionPoint(hitRecord);
	HitData reflectData = world.GetIntersection(Ray(p, r));
	glm::vec3 attenuation(1.0);
	t = refract(d, n, world.getRefractiveIndex(), refractiveIndex);
	Ray scatterRay = Ray(p, t);
	HitData scatterHit = world.GetIntersection(scatterRay, hitRecord.HitSurface);
	if (scatterHit.IsHit) {
		return scatterHit.HitSurface->Color(scatterHit, world, currRecurDepth + 1); 
	}
	else {
		return world.getBackgroundColor();
	}
}

glm::vec3 RefractionShader::refract(const glm::vec3& d, const glm::vec3& n, float exteriorIndex, float interiorIndex) {
	float nRatio = interiorIndex / exteriorIndex;
	float cosI = glm::dot(-d, n);
	float sin2T = pow(nRatio, 2) * (1.0 - pow(cosI, 2));
	// Total internal reflection check
	if (sin2T > 1.0) {
		// Return a zero magnitude vector for checking results
		return glm::vec3(0.0, 0.0, 0.0);
	}
	glm::vec3 tPerp = n * nRatio * cosI;
	tPerp += n * (float)(-sqrt(1 - sin2T));
	glm::vec3 tParallel = nRatio * d;
	return glm::normalize(tPerp + tParallel);
}