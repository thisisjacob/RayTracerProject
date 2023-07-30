#pragma once
#include <glm/glm.hpp>

struct CameraConfig {
	int imageWidth;
	int imageHeight;
	glm::vec3 eyePosition;
	glm::vec3 cameraDirection;
	float focalLength;
};