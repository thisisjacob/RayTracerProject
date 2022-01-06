#include "IdealSpecular.h"

IdealSpecular::IdealSpecular() {
	ambientCoeff = glm::tvec3<double>();
	ambientIntensity = glm::tvec3<double>();
	diffuseCoeff = glm::tvec3<double>();
	specularCoeff = glm::tvec3<double>();
	phongExponent = 0.0;
	matType = MaterialType::REFLECTIVE;
}

glm::tvec3<double> IdealSpecular::Shading(HitData& hitData, WorldState& world) {
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
		Ray shadowRay = Ray(surfacePoint, lVecUnit);
		// Check for objects blocking light source
		for (auto surface : world.GetSurfaces()) {
			surface->IsHit(shadowRay, 0.00000000001, shadowRecord.T, shadowRecord);
		}
		// If light source is blocked at pixel, do not calculate effect of that light source on the pixel
		if (!shadowRecord.IsHit) {
			// Calculate diffuse lighting
			lightCalc += intensity * diffuseCoeff * std::max(0.0, glm::dot(unitNormal, lVecUnit));
			// Calculate specular lighting
			glm::tvec3<double> vVecUnit = world.GetCamera().GetEye() - surfacePoint;
			vVecUnit = glm::normalize(vVecUnit);
			glm::tvec3<double> h = vVecUnit + lVecUnit;
			h = vVecUnit + lVecUnit;
			h /= h.length();
			h = glm::normalize(h);
			lightCalc += specularCoeff * intensity * std::pow(std::max(0.0, glm::dot(unitNormal, h)), phongExponent);
		}
	}
	glm::tvec3<double> r = glm::normalize(hitData.IntersectingRay.dir - 2 * (glm::dot(hitData.IntersectingRay.dir, unitNormal)) * unitNormal);
	// Calculate reflections
	lightCalc += RecursiveShading(Ray(surfacePoint, r), world, 0, 6);
	return glm::tvec3<double>(Clamp(lightCalc.x, 0.0, 1.0), Clamp(lightCalc.y, 0.0, 1.0), Clamp(lightCalc.z, 0.0, 1.0));
}

glm::tvec3<double> IdealSpecular::RecursiveShading(Ray ray, WorldState& world, int currIter, int maxIter) {
	HitData hit = world.GetIntersection(ray, 0.00000000001);
	glm::tvec3<double> color = glm::tvec3<double>(0.0);
	if (hit.IsHit && !hit.HitSurface) {
		int i = 0;
	}
	if (!hit.IsHit || currIter >= maxIter)
		return color;
	else
		color = hit.HitSurface->Color(hit, world);
	glm::tvec3<double> norm = hit.HitSurface->GetUnitSurfaceNormal(hit);
	glm::tvec3<double> d = glm::normalize(hit.IntersectingRay.dir);
	glm::tvec3<double> r = glm::normalize(d - 2 * (glm::dot(d, norm)) * norm);
	glm::tvec3<double> p = hit.HitSurface->GetIntersectionPoint(hit);
	// Recurse if hit material is also reflective
	if (hit.HitSurface->mat->matType == MaterialType::REFLECTIVE)
		return color * specularCoeff + specularCoeff * RecursiveShading(Ray(p, r), world, currIter + 1, maxIter);
	else
		return color * specularCoeff;
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