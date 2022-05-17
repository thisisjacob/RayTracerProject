#pragma once
#include "glm/glm.hpp"
#include <vector>

class Camera {
private:
	int imageWidth;
	int imageHeight;
	float focalLength;
	float aspectRatio;
	glm::vec3 eye;
public:
	Camera();
	Camera(int imageWidth, int imageHeight, float u, float v, float w, float focalLength);
	// Generates vectors holding each U and V component of the perspective vectors
	// This can be used for the main ray tracing loop
	float GetUValue(int xPixel) const;
	float GetVValue(int yPixel) const;
	const glm::vec3 GetEye() const;
	int GetImageWidth() const;
	int GetImageHeight() const;
	float GetFocalLength() const;
	float GetAspectRatio() const;
	// NOTE: Future versions could benefit from the addition of mutating functions
};