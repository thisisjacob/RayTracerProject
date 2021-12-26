#include "TestMat.h"

glm::tvec3<double> TestMat::Shading(HitData& hitData, WorldState& world) {
	return glm::tvec3<double>(0.0f, 1.0f, 0.0f);
}