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

float Camera::GetUValue(int xPixel) const {
	return aspectRatio * -0.5 + ((aspectRatio * 1.0) / imageWidth) * (float)xPixel;
}

float Camera::GetVValue(int yPixel) const {
	return 0.5 - (1.0 / imageHeight) * (float)(yPixel);
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

bool Camera::refreshImage(int newWidth, int newHeight) {
	this->imageWidth = newWidth;
	this->imageHeight = newHeight;
	this->aspectRatio = (float)newWidth / (float)newHeight;
	return true;
}