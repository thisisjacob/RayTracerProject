#include "Camera.h"

Camera::Camera() {
	this->imageWidth = 400;
	this->imageHeight = 400;
	this->focalLength = 1.0;
	aspectRatio = (float)imageWidth / (float)imageHeight;
	eye = glm::vec3(0.0, 0.0, 0.0);
}

Camera::Camera(int imageWidth, int imageHeight, float u, float v, float w, float focalLength) {
	this->imageWidth = imageWidth;
	this->imageHeight = imageHeight;
	this->focalLength = focalLength;
	aspectRatio = (float)imageWidth / (float)imageHeight;
	eye = glm::vec3(u, v, w);
}

std::vector<float> Camera::GenerateUComponents() const {
	std::vector<float> components;
	for (int col = 0; col < imageWidth; col++) {
		float u = aspectRatio * -0.5 + ((aspectRatio * 1.0) / imageWidth) * (float)(col);
		components.push_back(u);
	}
	return components;
}

std::vector<float> Camera::GenerateVComponents() const {
	std::vector<float> components;
	for (int row = 0; row < imageHeight; row++) {
		float v = 0.5 - (1.0 / imageHeight) * (float)(row);
		components.push_back(v);
	}
	return components;
}

const glm::vec3 Camera::GetEye() const {
	return eye;
}

int  Camera::GetImageWidth() const {
	return imageWidth;
}

int  Camera::GetImageHeight() const {
	return imageHeight;
}

float Camera::GetFocalLength() const {
	return focalLength;
}

float Camera::GetAspectRatio() const {
	return aspectRatio;
}