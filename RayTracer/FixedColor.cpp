#pragma once
#include "FixedColor.h";

FixedColor::FixedColor(glm::vec3 fixedColor) {
	color = glm::vec3(fixedColor);
}

glm::vec3 FixedColor::Shading(HitData& hitData, WorldState& world) {
	return glm::vec3(color);
}
