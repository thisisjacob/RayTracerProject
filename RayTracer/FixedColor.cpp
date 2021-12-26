#pragma once

#include "FixedColor.h";

FixedColor::FixedColor(glm::tvec3<double> fixedColor) {
	color = glm::tvec3<double>(fixedColor);
}

glm::tvec3<double> FixedColor::Shading(HitData& hitData, WorldState& world) {
	return glm::tvec3<double>(color);
}
