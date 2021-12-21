template <typename T>
T Clamp(T val, T min, T max) {
	static_assert(std::is_arithmetic<T>::value());

	if (val >= min && val <= max)
		return val;
	else if (val < min)
		return min;
	else
		return max;
}

int Normalize(int val, int maxOld, int maxNew) {
	return (int)(maxNew * (val / (float)(maxOld)));
}