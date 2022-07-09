#include "RefractionShader.h"

RefractionShader::RefractionShader(float refractiveIndex) {
	this->refractiveIndex = refractiveIndex;
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
	glm::vec3 attenuation(1.0);
	t = refract(d, n, world.getRefractiveIndex(), refractiveIndex);
	Ray scatterRay = Ray(p, t);
	HitData scatterHit = world.GetIntersection(scatterRay, hitRecord.HitSurface);
	
	if (scatterHit.IsHit) {
		//return scatterHit.HitSurface->Color(scatterHit, world, currRecurDepth + 1);
		return glm::vec3(0, 0, 0); 
	}
	else {
		return glm::vec3(1, 1, 1);
	}


	/*
	float c = 0.0;
	if (glm::dot(d, n) < 0.0) {
		refract(world, d, n, 1.0, t);
		HitData refracted = world.GetIntersection(Ray(p, t));
		if (refracted.IsHit) {
			return refracted.HitSurface->Color(refracted, world, currRecurDepth + 1);
		}
		else {
			return world.getBackgroundColor();
		}
		c = glm::dot(-d, n);
	}
	else {
		return glm::vec3(0, 0, 0);
		/*
		redColor = exp(-attenuationRed * hitRecord.T), greenColor = exp(-attenuationGreen * hitRecord.T), blueColor = exp(-attenuationBlue * hitRecord.T);
		if (refract(d, -n, 1 / 1.0, t)) {
			c = glm::dot(t, n);
		}
		else {
			return specularColor * world.GetIntersection(Ray(p, r)).HitSurface->Color(reflectData, world, currRecurDepth + 1);
		}
		
	}
	float R_0 = pow(1.0 - 1.0, 2) / pow(1.0 + 1.0, 2.0);
	float R = R_0 + (1 - R_0) * pow(1 - c, 5.0);
	
	
	if (reflectData.IsHit)
		return specularColor * (R * reflectData.HitSurface->Color(reflectData, world, currRecurDepth + 1) + (1.0f - R) * reflectData.HitSurface->Color(reflectData, world, currRecurDepth + 1));
	else
		return specularColor * R * world.getBackgroundColor() + (1.0f - R) * world.getBackgroundColor();
	*/
}

glm::vec3 RefractionShader::refract(const glm::vec3& d, const glm::vec3& n, float exteriorIndex, float interiorIndex) {
	float refractSqrt = 1.0 - ((pow(exteriorIndex, 2.0) * (1.0 - pow(glm::dot(d, n), 2.0))) / pow(interiorIndex, 2.0));
	// Total internal reflection, so return false
	if (refractSqrt < 0.0) { 
		// TODO: Currently just a junk value for testing, fix this
		return glm::vec3(1.0, 1.0, 1.0);
	}
	refractSqrt = sqrt(refractSqrt);
	glm::vec3 tPerp = (exteriorIndex * (d - n * glm::dot(d, n))) / interiorIndex;
	glm::vec3 tParallel = -n * refractSqrt;
	return glm::normalize(tPerp + tParallel);
}