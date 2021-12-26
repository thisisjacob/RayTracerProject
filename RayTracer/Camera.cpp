#include "Camera.h"

Camera::Camera() {
	this->imageWidth = 400;
	this->imageHeight = 400;
	this->focalLength = 1.0;
	aspectRatio = (double)imageWidth / (double)imageHeight;
	eye = glm::tvec3<double>(0.0, 0.0, 0.0);
}

Camera::Camera(int imageWidth, int imageHeight, double u, double v, double w, double focalLength) {
	this->imageWidth = imageWidth;
	this->imageHeight = imageHeight;
	this->focalLength = focalLength;
	aspectRatio = (double)imageWidth / (double)imageHeight;
	eye = glm::tvec3<double>(u, v, w);
}

std::vector<double> Camera::GenerateUComponents() {
	std::vector<double> components;
	for (int col = 0; col < imageWidth; col++) {
		double u = aspectRatio * -0.5 + ((aspectRatio * 1.0) / imageWidth) * (double)(col);
		components.push_back(u);
	}
	return components;
}

std::vector<double> Camera::GenerateVComponents() {
	std::vector<double> components;
	for (int row = 0; row < imageHeight; row++) {
		double v = 0.5 - (1.0 / imageHeight) * (double)(row);
		components.push_back(v);
	}
	return components;
}

const glm::tvec3<double> Camera::GetEye() {
	return eye;
}

int Camera::GetImageWidth() {
	return imageWidth;
}

int Camera::GetImageHeight() {
	return imageHeight;
}

double Camera::GetFocalLength() {
	return focalLength;
}

double Camera::GetAspectRatio() {
	return aspectRatio;
}


/*
	Camera(int imageWidth, int imageHeight, double u, double v, double w, double focalLength);
	// Generates vectors holding each U and V vector in order
	// This can be used for the main ray tracing loop
	const std::vector<double> GenerateUComponents();
	const std::vector<double> GenerateVComponents();
	const glm::tvec3<double> GetEye();
	int GetImageWidth();
	int GetImageHeight();
	double GetFocalLength();
	double GetAspectRatio();
*/