#include "IdealSpecular.h"

IdealSpecular::IdealSpecular() {
	ambientCoeff = glm::vec3();
	ambientIntensity = glm::vec3();
	diffuseCoeff = glm::vec3();
	specularCoeff = glm::vec3();
	phongExponent = 0.0;
	matType = MaterialType::REFLECTIVE;
}

glm::vec3 IdealSpecular::Shading(HitData& hitData, WorldState& world) {
	glm::vec3 unitNormal = hitData.HitSurface.get()->GetUnitSurfaceNormal(hitData);
	glm::vec3 surfacePoint = hitData.HitSurface.get()->GetIntersectionPoint(hitData);
	glm::vec3 lightCalc = glm::vec3(0.0);
	// Ambient calculation
	lightCalc += ambientCoeff * ambientIntensity;
	// Calculating shading effects from lights
	for (auto light : world.GetLights()) {
		glm::vec3 intensity = light.get()->lightIntensity;
		glm::vec3 lVecUnit = light.get()->lightPos - surfacePoint;
		lVecUnit = glm::normalize(lVecUnit);
		HitData shadowRecord;
		shadowRecord.IsHit = false;
		shadowRecord.T = std::numeric_limits<float>::infinity();
		Ray shadowRay = Ray(surfacePoint, lVecUnit);
		// Adds shading from a light source if not in shadow
		for (auto surface : world.GetSurfaces()) {
			surface->IsHit(shadowRay, EPSILON, shadowRecord.T, shadowRecord);
		}
		if (!shadowRecord.IsHit) {
			// Calculate diffuse lighting
			lightCalc += intensity * diffuseCoeff * std::max(0.0f, glm::dot(unitNormal, lVecUnit));
		}
	}
	// Calculating reflection ray and reflection shading
	glm::vec3 r = glm::normalize(hitData.IntersectingRay.dir - 2 * (glm::dot(hitData.IntersectingRay.dir, unitNormal)) * unitNormal);
	lightCalc += RecursiveShading(Ray(surfacePoint, r), world, 0);
	return glm::vec3(Clamp(lightCalc.x, 0.0f, 1.0f), Clamp(lightCalc.y, 0.0f, 1.0f), Clamp(lightCalc.z, 0.0f, 1.0f));
}

glm::vec3 IdealSpecular::RecursiveShading(Ray ray, WorldState& world, int currIter) {
	HitData hit = world.GetIntersection(ray, EPSILON);
	glm::vec3 color = glm::vec3(0.0);
	// Prevent infinite recursion
	if (!hit.IsHit || currIter >= MAX_REFLECTION_RECURSION_DEPTH)
		return color;
	else if (hit.HitSurface->mat->matType != MaterialType::REFLECTIVE) { // Non reflective surface
		color = hit.HitSurface->Color(hit, world);
		return color * specularCoeff;
	}
	else if (hit.HitSurface->mat->matType == MaterialType::REFLECTIVE) { // Reflective surface, recurse reflection
		glm::vec3 norm = hit.HitSurface->GetUnitSurfaceNormal(hit);
		glm::vec3 d = glm::normalize(hit.IntersectingRay.dir);
		glm::vec3 r = glm::normalize(d - 2 * (glm::dot(d, norm)) * norm);
		glm::vec3 p = hit.HitSurface->GetIntersectionPoint(hit);
		return color * specularCoeff + specularCoeff * RecursiveShading(Ray(p, r), world, currIter + 1);
	}
	return color;
}

bool IdealSpecular::SetAmbientCoeff(glm::vec3 newAmbient) {
	ambientCoeff = newAmbient;
	return true;
}

bool IdealSpecular::SetAmbientIntensity(glm::vec3 newIntensity) {
	ambientIntensity = newIntensity;
	return true;
}

bool IdealSpecular::SetDiffuseCoeff(glm::vec3 newDiffuse) {
	diffuseCoeff = newDiffuse;
	return true;
}

bool IdealSpecular::SetSpecularCoeff(glm::vec3 newSpecular) {
	specularCoeff = newSpecular;
	return true;
}

bool IdealSpecular::SetPhongExponent(float exponent) {
	phongExponent = exponent;
	return true;
}