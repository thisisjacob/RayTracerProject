#pragma once
#include <glm/glm.hpp>
#include "HitData.h"
#include "Ray.h"
#include "WorldState.h"

enum class MaterialType {
	BASIC,
	REFLECTIVE
};

class Material {
public:
	MaterialType matType;
	virtual glm::vec3 Shading(HitData& hitData, WorldState& world) = 0;
};