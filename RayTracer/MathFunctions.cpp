#include "MathFunctions.h"

glm::vec3 clampVec3(glm::vec3 val, float min, float max)
{
	val.x = clamp(val.x, min, max);
	val.y = clamp(val.y, min, max);
	val.z = clamp(val.z, min, max);
	return val;
}

glm::vec3 clampVec3Color(glm::vec3 color) {
	return clampVec3(color, MIN_COLOR_VAL, MAX_COLOR_VAL);
}

bool recursionLimitHit(int currRecurDepth) {
	assert(currRecurDepth >= 0);
	return currRecurDepth >= MAX_RECUR_DEPTH;
}