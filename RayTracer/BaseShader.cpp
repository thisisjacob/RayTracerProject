#pragma once
#include "BaseShader.h"

BlinnPhong::BlinnPhong() {
	ambientCoeff = glm::tvec3<double>();
	ambientIntensity = glm::tvec3<double>();
	diffuseCoeff = glm::tvec3<double>();
	specularCoeff = glm::tvec3<double>();
	phongExponent = 0.0;
}

glm::tvec3<double> BlinnPhong::Shading(HitData& hitData, WorldState& world) {
	glm::tvec3<double> unitNormal = hitData.HitSurface.get()->GetUnitSurfaceNormal(hitData);
	glm::tvec3<double> surfacePoint = hitData.HitSurface.get()->GetIntersectionPoint(hitData);
	glm::tvec3<double> lightCalc = glm::tvec3<double>(0.0);
	// Ambient calculation, always exists
	lightCalc += ambientCoeff * ambientIntensity;
	// Calculate lighting
	for (auto light : world.GetLights()) {
		glm::tvec3<double> intensity = light.get()->lightIntensity;
		glm::tvec3<double> lVecUnit = light.get()->lightPos - surfacePoint;
		lVecUnit = glm::normalize(lVecUnit);
		HitData shadowRecord;
		shadowRecord.IsHit = false;
		shadowRecord.T = std::numeric_limits<double>::infinity();
		// Check for objects blocking light source
		for (auto surface : world.GetSurfaces()) {
			Ray shadowRay = Ray(surfacePoint, -lVecUnit.z, lVecUnit.x, lVecUnit.y);
			surface->IsHit(shadowRay, 0.0000000000001, std::numeric_limits<double>::infinity(), shadowRecord);
			
		}
		// If light source is blocked at pixel, do not calculate effect of that light source on the pixel
		if (!shadowRecord.IsHit) {
			// Calculate diffuse lighting
			lightCalc += intensity * diffuseCoeff * std::max(0.0, glm::dot(unitNormal, lVecUnit));
			// Calculate specular lighting
			glm::tvec3<double> vVecUnit = world.GetCamera().GetEye() - surfacePoint;
			vVecUnit = glm::normalize(vVecUnit);
			glm::tvec3<double> h = vVecUnit + lVecUnit;
			h /= (vVecUnit + lVecUnit).length();
			h = glm::normalize(h);
			lightCalc += specularCoeff * intensity * std::pow(std::max(0.0, glm::dot(unitNormal, h)), phongExponent);
		}
	}

	return glm::tvec3<double>(Clamp(lightCalc.x, 0.0, 1.0), Clamp(lightCalc.y, 0.0, 1.0), Clamp(lightCalc.z, 0.0, 1.0));
}

bool BlinnPhong::SetAmbientCoeff(glm::tvec3<double> newAmbient) {
	ambientCoeff = newAmbient;
	return true;
}

bool BlinnPhong::SetAmbientIntensity(glm::tvec3<double> newIntensity) {
	ambientIntensity = newIntensity;
	return true;
}

bool BlinnPhong::SetDiffuseCoeff(glm::tvec3<double> newDiffuse) {
	diffuseCoeff = newDiffuse;
	return true;
}

bool BlinnPhong::SetSpecularCoeff(glm::tvec3<double> newSpecular) {
	specularCoeff = newSpecular;
	return true;
}

bool BlinnPhong::SetPhongExponent(double exponent) {
	phongExponent = exponent;
	return true;
}