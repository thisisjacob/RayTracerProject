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

// TODO: Currently not functioning as expected
int Normalize(int val, int maxOld, int maxNew) {
	return (int)(maxNew * (val / (float)(maxOld)));
}