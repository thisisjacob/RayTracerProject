#pragma once
#include "BaseShader.h"

BlinnPhong::BlinnPhong() {
	ambientCoeff = glm::vec3();
	ambientIntensity = glm::vec3();
	diffuseCoeff = glm::vec3();
	specularCoeff = glm::vec3();
	phongExponent = 0.0;
	matType = MaterialType::BASIC;
}

glm::vec3 BlinnPhong::Shading(HitData& hitData, WorldState& world) {
	glm::vec3 unitNormal = hitData.HitSurface.get()->GetUnitSurfaceNormal(hitData);
	glm::vec3 surfacePoint = hitData.HitSurface.get()->GetIntersectionPoint(hitData);
	glm::vec3 lightCalc = glm::vec3(0.0);
	// Ambient calculation, always exists
	lightCalc += ambientCoeff * ambientIntensity;
	// Calculate lighting
	for (auto light : world.GetLights()) {
		glm::vec3 intensity = light.get()->lightIntensity;
		glm::vec3 lVecUnit = light.get()->lightPos - surfacePoint;
		lVecUnit = glm::normalize(lVecUnit);
		HitData shadowRecord;
		shadowRecord.IsHit = false;
		shadowRecord.T = std::numeric_limits<float>::infinity();
		Ray shadowRay = Ray(surfacePoint, lVecUnit);
		// Check for objects blocking light source
		for (auto surface : world.GetSurfaces()) {
			surface->IsHit(shadowRay, EPSILON, shadowRecord.T, shadowRecord);
		}
		// If light source is blocked at pixel, do not calculate effect of that light source on the pixel
		if (!shadowRecord.IsHit) {
			// Calculate diffuse lighting
			lightCalc += intensity * diffuseCoeff * std::max(0.0f, glm::dot(unitNormal, lVecUnit));
			// Calculate specular lighting
			glm::vec3 vVecUnit = world.GetCamera().GetEye() - surfacePoint;
			vVecUnit = glm::normalize(vVecUnit);
			glm::vec3 h = vVecUnit + lVecUnit;
			h = vVecUnit + lVecUnit;
			h /= h.length();
			h = glm::normalize(h);
			lightCalc += specularCoeff * intensity * (float)std::pow(std::max(0.0f, glm::dot(unitNormal, h)), phongExponent);
		}
	}

	return glm::vec3(Clamp(lightCalc.x, 0.0f, 1.0f), Clamp(lightCalc.y, 0.0f, 1.0f), Clamp(lightCalc.z, 0.0f, 1.0f));
}

bool BlinnPhong::SetAmbientCoeff(glm::vec3 newAmbient) {
	ambientCoeff = newAmbient;
	return true;
}

bool BlinnPhong::SetAmbientIntensity(glm::vec3 newIntensity) {
	ambientIntensity = newIntensity;
	return true;
}

bool BlinnPhong::SetDiffuseCoeff(glm::vec3 newDiffuse) {
	diffuseCoeff = newDiffuse;
	return true;
}

bool BlinnPhong::SetSpecularCoeff(glm::vec3 newSpecular) {
	specularCoeff = newSpecular;
	return true;
}

bool BlinnPhong::SetPhongExponent(float exponent) {
	phongExponent = exponent;
	return true;
}