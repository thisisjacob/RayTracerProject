#include "RayTracer.h"
#include "MathFunctions.h"
#include "TestMat.h";

RayTracer::RayTracer(int imageWidth, int imageHeight, float u, float v, float w, float focalLength) {
	this->imageWidth = imageWidth;
	this->imageHeight = imageHeight;
	this->focalLength = focalLength;
	eye = glm::vec3(u, v, w);
	objects.push_back(std::shared_ptr<Surface>(new Sphere(0.0, 0.0, 0.0, 3.0, new TestMat())));
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

	// Calculating output data for each pixel of image
	for (int v = -(imageHeight / 2); v < imageHeight / 2; v++) {
		for (int u = -(imageWidth / 2); u < imageWidth / 2; u++) {
			Ray ray = Ray(eye, focalLength, u, v);
			// Finding closest object hit
			HitData hitData;
			hitData.IsHit = false;
			hitData.T = std::numeric_limits<double>::infinity();
			for (const auto& s : objects) {
				bool isHit = (*s).IsHit(ray, 0, hitData.T, hitData);
				if (isHit) {
					hitData.HitSurface = s;
					hitData.IntersectingRay = ray;
				}
			}
			
			// Writing color data to file
			if (hitData.IsHit) {
				// Found closest object, determine shading
				glm::vec3 color = hitData.HitSurface->Color(hitData);
				fileWriter << Normalize(color.x, 1.0, 255) << " " << Normalize(color.y, 1.0, 255) << " " << Normalize(color.z, 1.0, 255) << "\n";
			}
			else // TODO: Change normalize function to prevent negative values
				fileWriter << Normalize(u, imageWidth, 255) << " " << Normalize(v, imageHeight, 255) << " 128\n";
		}
	}
	fileWriter.close();

	return true;
}