#include "RefractionShader.h"

RefractionShader::RefractionShader(float refractiveIndex, glm::vec3 attenuation) {
	this->refractiveIndex = refractiveIndex;
	this->attenuationRed = attenuation.r;
	this->attenuationGreen = attenuation.g;
	this->attenuationBlue = attenuation.b;
}

glm::vec3 RefractionShader::Shading(HitData& hitRecord, WorldState& world, int currRecurDepth) {
	if (recursionLimitHit(currRecurDepth)) {
		return glm::vec3(0, 0, 0);
	}

	glm::vec3 r = reflectRay(hitRecord).dir;
	glm::vec3 d = hitRecord.IntersectingRay.dir;
	glm::vec3 n = hitRecord.HitSurface->GetUnitSurfaceNormal(hitRecord);
	glm::vec3 t;
	glm::vec3 p = hitRecord.HitSurface->GetIntersectionPoint(hitRecord);
	HitData reflectData = world.GetIntersection(Ray(p, r));

	float c = 0.0;
	float redColor = 0.0, greenColor = 0.0, blueColor = 0.0;
	if (glm::dot(d, n) < 0.0) {
		refract(d, n, 1.0, t);
		c = glm::dot(-d, n);
		redColor = 1, greenColor = 1, blueColor = 1;
	}
	else {
		redColor = exp(-attenuationRed), greenColor = exp(-attenuationGreen), blueColor = exp(-attenuationBlue);
		if (refract(d, -n, 1 / 1.0, t)) {
			c = glm::dot(t, n);
		}
		else {
			return world.GetIntersection(Ray(p, r)).HitSurface->Color(reflectData, world);
		}
	}
	float R_0 = pow(1.0 - 1.0, 2) / pow(1.0 + 1.0, 2.0);
	float R = R_0 + (1 - R_0) * pow(1 - c, 5.0);
	
	
	//return glm::vec3(0.5, 0.5, 0.5);
	std::cout << reflectData.IsHit;
	if (reflectData.IsHit)
		return R * reflectData.HitSurface->Color(reflectData, world) + (1.0f - R) * reflectData.HitSurface->Color(reflectData, world);
	else
		return glm::vec3(0.5, 0.5, 0.5);
}

bool RefractionShader::refract(const glm::vec3& d, const glm::vec3& n, float refractiveIndex, glm::vec3& t) {
	// TODO: Get global refractive index for first pow
	const float GLOBAL_REFRACTIVE_INDEX = 1.0;
	float refractSqrt = 1.0 - (pow(GLOBAL_REFRACTIVE_INDEX, 2.0) * (1 - pow(glm::dot(d, n), 2.0)) / pow(refractiveIndex, 2.0));
	// Total internal reflection, so return false
	if (refractSqrt < 0) { return false; }
	refractSqrt = sqrt(refractSqrt);
	t = (GLOBAL_REFRACTIVE_INDEX * (d - n * glm::dot(d, n))) / refractiveIndex;
	t -= n * refractSqrt;
}