#pragma once
#include "Material.h"

class TestMat : public Material {
public:
	glm::vec3 Shading(HitData& hitData, WorldState& world);
};