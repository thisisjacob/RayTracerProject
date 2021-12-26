#pragma once

#include "glm/glm.hpp";

struct Light {
	glm::tvec3<double> lightPos;
	double intensity;
};