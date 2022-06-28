#include "Camera.h"

Camera::Camera() {
	this->imageWidth = 400;
	this->imageHeight = 400;
	this->focalLength = 1.0;
	aspectRatio = (float)imageWidth / (float)imageHeight;
	eye = glm::vec3(0.0, 0.0, 0.0);
}

Camera::Camera(int imageWidth, int imageHeight, glm::vec3 eyePos, glm::vec3 dir, float focalLength) {
	// Must have a valid direction
	assert(glm::length(dir) > 0.0);
	this->imageWidth = imageWidth;
	this->imageHeight = imageHeight;
	// Ensure focal length matches the direction of the passed dir
	this->focalLength = abs(focalLength);
	this->aspectRatio = (float)imageWidth / (float)imageHeight;
	this->eye = glm::vec3(eyePos);
	this->dir = glm::normalize(dir);
}

float Camera::GetUValue(int xPixel) const {
	return aspectRatio * -0.5 + ((aspectRatio * 1.0) / imageWidth) * (float)xPixel;
}

float Camera::GetVValue(int yPixel) const {
	return 0.5 - (1.0 / imageHeight) * (float)(yPixel);
}

glm::vec3 Camera::getEye() const {
	return eye;
}

glm::vec3 Camera::getDir() const {
	return dir;
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

bool Camera::resizeImagePlane(int newWidth, int newHeight) {
	this->imageWidth = newWidth;
	this->imageHeight = newHeight;
	this->aspectRatio = (float)newWidth / (float)newHeight;
	return true;
}