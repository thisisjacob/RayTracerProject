#include "RayTracer.h"
#include "MathFunctions.h"

RayTracer::RayTracer(int imageWidth, int imageHeight, float u, float v, float w, float focalLength) {
	this->imageWidth = imageWidth;
	this->imageHeight = imageHeight;
	this->focalLength = focalLength;
	eye = glm::vec3(w, u, v);
}

bool RayTracer::Render() {
	std::ofstream fileWriter("test.ppm");
	if (!fileWriter) {
		std::cerr << "Error creating file.\n";
		return false;
	}
	// Image header
	fileWriter << "P3\n";
	fileWriter << imageWidth << " " << imageHeight << "\n";
	fileWriter << "255\n";
	for (int v = 0; v < imageHeight; v++) {
		for (int u = 0; u < imageWidth; u++) {
			Ray ray = Ray(eye, focalLength, imageWidth, imageHeight);
			fileWriter << Normalize(u, imageWidth, 255) << " " << Normalize(v, imageHeight, 255) << " 128\n";
		}
	}
	fileWriter.close();

	return true;
}