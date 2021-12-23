#pragma once
#include "Material.h"

class FixedColor : public Material {
private:
	glm::vec3 color;
public:
	glm::vec3 Shading(HitData& hitData);
	FixedColor(glm::vec3 fixedColor);
};
