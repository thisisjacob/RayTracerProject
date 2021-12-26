#pragma once

template <typename T>
T Clamp(T val, T min, T max) {

	if (val >= min && val <= max)
		return val;
	else if (val < min)
		return min;
	else
		return max;
}