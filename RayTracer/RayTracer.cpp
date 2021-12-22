#include "RayTracer.h"
#include "MathFunctions.h"

RayTracer::RayTracer(int imageWidth, int imageHeight, float u, float v, float w, float focalLength) {
	this->imageWidth = imageWidth;
	this->imageHeight = imageHeight;
	this->focalLength = focalLength;
	eye = glm::vec3(u, v, w);
	objects.push_back(std::unique_ptr<Surface>(new Sphere(0.0, 0.0, 0.0, 3.0)));
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

	for (int v = -(imageHeight / 2); v < imageHeight / 2; v++) {
		for (int u = -(imageWidth / 2); u < imageWidth / 2; u++) {
			Ray ray = Ray(eye, focalLength, u, v);
			HitData hitData;
			hitData.IsHit = false;
			hitData.T = std::numeric_limits<double>::infinity();
			for (const auto& s : objects)
				(*s).IsHit(ray, 0, hitData.T, hitData);
			// Test to check for hitting
			if (hitData.IsHit)
				fileWriter << 255 << " 0 0\n";
			else 
				fileWriter << Normalize(u, imageWidth, 255) << " " << Normalize(v, imageHeight, 255) << " 128\n";
		}
	}
	fileWriter.close();

	return true;
}