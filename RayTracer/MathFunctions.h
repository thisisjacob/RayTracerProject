#pragma once

// Used for restricting values to be in the range of [min, max]
template <typename T>
T Clamp(T val, T min, T max) {

	if (val >= min && val <= max)
		return val;
	else if (val < min)
		return min;
	else
		return max;
}

// A uniform constant for small values
const float EPSILON = 0.0001f;