#include "BoundingBox.h"

BoundingBox::BoundingBox(const glm::vec3& min, const glm::vec3& max) {
	this->min = glm::vec3(min);
	this->max = glm::vec3(max);
}

glm::vec3 BoundingBox::getMin() { return min; }

glm::vec3 BoundingBox::getMax() { return max; }