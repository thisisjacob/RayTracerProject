#include "RayTracer.h"
#include "MathFunctions.h"
#include "TestMat.h"
#include "FixedColor.h"

RayTracer::RayTracer(int imageWidth, int imageHeight, float u, float v, float w, float focalLength) {
	this->imageWidth = imageWidth;
	this->imageHeight = imageHeight;
	this->focalLength = focalLength;
	eye = glm::vec3(u, v, w);
	objects.push_back(std::shared_ptr<Surface>(new Sphere(0.0, 0.0, 0.0, 1.0, new FixedColor(glm::vec3(0.5, 0.2, 0.7)))));
	// TODO: V currently moves sphere in opposite order, fix
	objects.push_back(std::shared_ptr<Surface>(new Sphere(0.0, 0.0, 0.0, 1.0, new FixedColor(glm::vec3(0.2, 0.2, 1.0)))));
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
	for (double v = 0.5; v > -0.5; v -= (1.0 / imageHeight)) {
		for (double u = -0.5; u < 0.5; u += (1.0 / imageWidth)) {
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
				fileWriter << 255 * color.x << " " << 255 * color.y << " " << 255 * color.z << "\n";
			}
			else // TODO: Change normalize function to prevent negative values
				fileWriter << Normalize(u, imageWidth, 255) << " " << Normalize(v, imageHeight, 255) << " 128\n";
		}
	}
	fileWriter.close();

	return true;
}