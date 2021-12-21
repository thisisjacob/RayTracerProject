#include "RayTracer.h"

RayTracer::RayTracer(int imageWidth, int imageHeight, int u, int v, int focalLength) {
	this->imageWidth = imageWidth;
	this->imageHeight = imageHeight;
	this->focalLength = focalLength;
	eye = glm::vec3(0.0, u, v);
}

bool RayTracer::Render() {
	for (int j = 0; j < imageHeight; j++) {
		for (int i = 0; i < imageWidth; i++) {
			Ray ray = Ray(eye, focalLength, i - (imageWidth / 2), j - (imageHeight / 2));
		}
	}

	return true;
}