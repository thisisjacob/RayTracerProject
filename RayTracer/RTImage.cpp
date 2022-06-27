#include "RTImage.h"

RTImage::RTImage() : pixels{ 0 }, height{ 0 }, width{ 0 } {}

RTImage::RTImage(int newWidth, int newHeight) : width{ newWidth }, height{ newHeight }, pixels{ width * height } {
	// Test for valid sizes
	assert(newWidth >= 0 && newHeight >= 0);
}

int RTImage::getHeight() { return height; }

void RTImage::setHeight(int newHeight) { height = newHeight; }

int RTImage::getWidth() { return width; }

void RTImage::setWidth(int newWidth) { width = newWidth; }

void RTImage::erasePixels() {
	pixels = std::vector<glm::vec3>(width * height);
}

void RTImage::resizePixels(int newWidth, int newHeight) {
	// Test for valid sizes
	assert(newWidth >= 0 && newHeight >= 0);
	pixels = std::vector<glm::vec3>(newWidth * newHeight);
	width = newWidth;
	height = newHeight;
}