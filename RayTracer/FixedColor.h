#pragma once
#include "Material.h"

class FixedColor : public Material {
private:
	glm::tvec3<double> color;
public:
	glm::tvec3<double> Shading(HitData& hitData, WorldState& world);
	FixedColor(glm::tvec3<double> fixedColor);
};
