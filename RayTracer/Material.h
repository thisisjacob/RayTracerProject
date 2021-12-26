#pragma once
#include <glm/glm.hpp>
#include "HitData.h"
#include "Ray.h"
#include "WorldState.h"

class Material {
public:
	virtual glm::vec3 Shading(HitData& hitData, WorldState& world) = 0;
};