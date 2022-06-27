#pragma once
#include "Triangle.h"
#include "glm/glm.hpp"
#include <vector>

struct Mesh {
	std::vector<std::shared_ptr<Surface>> surfaces;
};