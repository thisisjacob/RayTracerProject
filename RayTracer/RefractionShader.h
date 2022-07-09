#pragma once
#include "Material.h"
#include "RayFunctions.h"
#include "MathFunctions.h"

class RefractionShader : public Material {
private:
	float refractiveIndex;
public:
	RefractionShader(float refractiveIndex);
	glm::vec3 Shading(HitData& hitData, WorldState& world, int currRecurDepth);
	// Calculates refraction
	// If there is total internal reflection, then false is returned and no changes are made
	// Otherwise, true is returned, and the value of t is stored in the passed reference t
	glm::vec3 refract(const glm::vec3& d, const glm::vec3& n, float exteriorIndex, float interiorIndex);
};