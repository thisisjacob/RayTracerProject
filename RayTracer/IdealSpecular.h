#pragma once
#include "Material.h"
#include "MathFunctions.h"



// Maximum number of recursions calling the RecursiveShading function
// This is needed in order to prevent infinite recursion when there are several reflective materials
const int MAX_REFLECTION_RECURSION_DEPTH = 5;

// Shader used for ideal reflective surfaces (such as perfect mirrors)
class IdealSpecular : public Material {
private:
	glm::vec3 ambientCoeff;
	glm::vec3 ambientIntensity;
	glm::vec3 diffuseCoeff;
	glm::vec3 specularCoeff;
	float phongExponent;
public:
	IdealSpecular();
	glm::vec3 Shading(HitData& hitData, WorldState& world);
	// Called to recursively calculate shading in the event of several reflections
	glm::vec3 RecursiveShading(Ray ray, WorldState& world, int currIter);
	bool SetAmbientCoeff(glm::vec3 newAmbient);
	bool SetAmbientIntensity(glm::vec3 newIntensity);
	bool SetDiffuseCoeff(glm::vec3 newDiffuse);
	bool SetSpecularCoeff(glm::vec3 newSpecular);
	bool SetPhongExponent(float exponent);
};