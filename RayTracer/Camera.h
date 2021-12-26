#pragma once
#include "glm/glm.hpp"
#include <vector>

class Camera {
private:
	int imageWidth;
	int imageHeight;
	double focalLength;
	double aspectRatio;
	glm::tvec3<double> eye;
public:
	Camera();
	Camera(int imageWidth, int imageHeight, double u, double v, double w, double focalLength);
	// Generates vectors holding each U and V vector in order
	// This can be used for the main ray tracing loop
	std::vector<double> GenerateUComponents();
	std::vector<double> GenerateVComponents();
	const glm::tvec3<double> GetEye();
	int GetImageWidth();
	int GetImageHeight();
	double GetFocalLength();
	double GetAspectRatio();
	// NOTE: Future versions could benefit from the addition of mutating functions
};