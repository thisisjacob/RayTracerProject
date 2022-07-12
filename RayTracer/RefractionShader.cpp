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
	glm::vec3 t = refract(d, n, world.getRefractiveIndex(), refractiveIndex);
	glm::vec3 p = hitRecord.HitSurface->GetIntersectionPoint(hitRecord);
	// Get intersection results of reflection and refraction
	HitData reflectData = world.GetIntersection(Ray(p, r), EPSILON);
	HitData refractData = world.GetIntersection(Ray(p, t), hitRecord.HitSurface);

	// Get percentage of reflected light
	float rVal = reflectanceSchlick(d, n, world.getRefractiveIndex(), refractiveIndex);
	// Get final result
	glm::vec3 lightCalc(0.0);
	// Get refracted light
	if (refractData.IsHit) {
		lightCalc += (1.0f - rVal) * refractData.HitSurface->Color(refractData, world, currRecurDepth + 1);
	}
	else {
		lightCalc += (1.0f - rVal) * world.getBackgroundColor();
	}
	// Get reflected light
	if (reflectData.IsHit) {
		lightCalc += rVal * reflectData.HitSurface->Color(reflectData, world, currRecurDepth + 1);
	}
	else {
		lightCalc += rVal * world.getBackgroundColor();
	}

	return clampVec3Color(lightCalc);
}

glm::vec3 RefractionShader::refract(glm::vec3 d, glm::vec3 n, float exteriorIndex, float interiorIndex) {
	float nRatio = exteriorIndex / interiorIndex;
	float cosD = std::min(glm::dot(-d, n), 1.0f);
	float sin2T = nRatio * nRatio * (1.0 - cosD * cosD);
	// Total internal reflection check
	if (sin2T > 1.0) {
		// Return a zero magnitude vector for checking results
		return glm::vec3(0.0, 0.0, 0.0);
	}
	glm::vec3 tPerp = n * nRatio * cosD;
	tPerp += n * (float)(-sqrt(1.0 - sin2T));
	glm::vec3 tParallel = nRatio * d;
	return tPerp + tParallel;
}

float RefractionShader::reflectanceFresnel(glm::vec3 d, glm::vec3 n, float exteriorIndex, float interiorIndex) {
	float nRatio = exteriorIndex / interiorIndex;
	float cosD = std::min(glm::dot(-d, n), 1.0f);
	float sin2T = nRatio * nRatio * (1.0 - cosD * cosD);
	// Total internal reflection reached
	if (sin2T > 1.0) return 1.0;
	float cosT = sqrt(1.0 - sin2T);
	float rPerp = (exteriorIndex * cosD - interiorIndex * cosT) / (exteriorIndex * cosT + interiorIndex * cosT);
	float rParallel = (interiorIndex * cosD - exteriorIndex * cosT) / (interiorIndex * cosD + exteriorIndex * cosT);
	return (rPerp * rPerp + rParallel * rParallel) / 2.0;
}

float RefractionShader::reflectanceSchlick(glm::vec3 d, glm::vec3 n, float exteriorIndex, float interiorIndex) {
	float r0 = (exteriorIndex - interiorIndex) / (exteriorIndex + interiorIndex);
	r0 *= r0;
	float cosD = -glm::dot(n, d);
	if (exteriorIndex > interiorIndex) {
		float nRatio = exteriorIndex / interiorIndex;
		float sin2T = nRatio * nRatio * (1.0 - cosD * cosD);
		if (sin2T > 1.0) { return 1.0; }
		cosD = sqrt(1.0 - sin2T);
	}
	double x = 1.0 - cosD;
	return r0 + (1.0 - r0) * pow(x, 5.0);
}
