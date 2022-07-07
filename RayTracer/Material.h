#pragma once
#include <glm/glm.hpp>
#include "HitData.h"
#include "WorldState.h"

class HitData;
class WorldState;

enum class MaterialType {
	BASIC,
	REFLECTIVE
};

class Material {
public:
	MaterialType matType;
	// Returns the color determined by the material's shading function
	// currRecurrDepth should be iterated when a shading function is called within another shading function
	// This is used to prevent infinite loops when handling reflections and refraction
	virtual glm::vec3 Shading(HitData& hitData, WorldState& world, int currRecurrDepth) = 0;
};