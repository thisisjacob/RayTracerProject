#pragma once
#include "glm/glm.hpp"
// Used for restricting the components of a vec3 into the range of [min, max]
glm::vec3 clampVec3(glm::vec3 val, float min, float max);
// Clamps the components of a glm::vec3 color into the range [MIN_COLOR_VAL, MAX_COLOR_VAL]
glm::vec3 clampVec3Color(glm::vec3 color);


// Used for restricting values to be in the range of [min, max]
template <typename T>
T clamp(T val, T min, T max) {

	if (val >= min && val <= max)
		return val;
	else if (val < min)
		return min;
	else
		return max;
}

// A uniform constant for small values
const float EPSILON = 0.0001f;
// Maximum number of recursions for shading
const int MAX_RECUR_DEPTH = 6;
// Checks if the recursion limit has been reached
bool recursionLimitHit(int currRecurDepth);

// Color values must be within this range
const float MAX_COLOR_VAL = 1.0;
const float MIN_COLOR_VAL = 0.0;