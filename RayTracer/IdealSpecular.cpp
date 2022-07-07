#include "IdealSpecular.h"

IdealSpecular::IdealSpecular() {
	ambientCoeff = glm::vec3();
	ambientIntensity = glm::vec3();
	diffuseCoeff = glm::vec3();
	specularCoeff = glm::vec3();
	phongExponent = 0.0;
	matType = MaterialType::REFLECTIVE;
}

glm::vec3 IdealSpecular::Shading(HitData& hitData, WorldState& world, int currRecurDepth) {
	// Recursion limit reached, so end the recursion
	if (recursionLimitHit(currRecurDepth)) {
		return glm::vec3(0, 0, 0);
	}

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
			shadowRecord = surface->IsHit(surface, shadowRay, EPSILON, shadowRecord.T, shadowRecord);
		}
		if (!shadowRecord.IsHit) {
			// Calculate diffuse lighting
			lightCalc += intensity * diffuseCoeff * std::max(0.0f, glm::dot(unitNormal, lVecUnit));
		}
	}
	// Get reflections from other surfaces
	Ray reflectedRay = reflectRay(hitData);
	HitData reflectedHit = world.GetIntersection(reflectedRay, EPSILON);
	if (reflectedHit.IsHit) {
		lightCalc += specularCoeff * reflectedHit.HitSurface->Color(reflectedHit, world, ++currRecurDepth);
	}
	return clampVec3Color(lightCalc);
}

glm::vec3 IdealSpecular::shadeReflectedColor(glm::vec3 reflectedColor) {
	return reflectedColor * specularCoeff;
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
		Ray reflectedRay = reflectRay(hit);
		return color * specularCoeff + specularCoeff * RecursiveShading(reflectedRay, world, currIter + 1);
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