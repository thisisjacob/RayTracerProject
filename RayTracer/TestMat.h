#pragma once
#include "Material.h"

class TestMat : public Material {
public:
	glm::tvec3<double> Shading(HitData& hitData, WorldState& world);
};