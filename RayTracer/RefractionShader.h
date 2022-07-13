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
	glm::vec3 refract(glm::vec3 d, glm::vec3 n, float exteriorIndex, float interiorIndex);
	// Calculates the reflectance percentage using the traditional Fresnel formula
	float reflectanceFresnel(glm::vec3 d, glm::vec3 n, float exteriorIndex, float interiorIndex);
	// Calculates the reflectance percentage using the Schlick approximation
	// Faster, with minor decreases in accuracy. Should typically be used over the Fresnel version
	float reflectanceSchlick(glm::vec3 d, glm::vec3 n, float exteriorIndex, float interiorIndex);
};