#pragma once
#include "glm/glm.hpp"
class BoundingBox {
private:
	glm::vec3 min;
	glm::vec3 max;
public:
	BoundingBox(const glm::vec3& min, const glm::vec3& max);
	glm::vec3 getMin();
	glm::vec3 getMax();
};