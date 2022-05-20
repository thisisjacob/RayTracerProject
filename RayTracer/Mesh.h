#pragma once
#include "Triangle.h"
#include "glm/glm.hpp"
#include <vector>

struct Mesh {
	std::vector<Triangle> surfaces;
};