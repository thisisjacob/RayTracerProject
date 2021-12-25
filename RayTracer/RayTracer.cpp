#include "RayTracer.h"
#include "MathFunctions.h"
#include "TestMat.h"
#include "FixedColor.h"
#include "Lambertian.h"

RayTracer::RayTracer(int imageWidth, int imageHeight, float u, float v, float w, float focalLength, WorldState world) {
	this->imageWidth = imageWidth;
	this->imageHeight = imageHeight;
	this->focalLength = focalLength;
	aspectRatio = (double)imageWidth / (double)imageHeight;
	eye = glm::vec3(u, v, w);
	this->world = world;
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
	for (int row = 0; row < imageHeight; row++) {
		for (int col = 0; col < imageWidth; col++) {
			// Increases range of u to account for aspect ratio (assuming widescreen)
			double u = aspectRatio * -0.5 + ((aspectRatio * 1.0) / imageWidth) * (double)(col);
			double v = 0.5 - (1.0 / imageHeight) * (double)(row);
			Ray ray = Ray(eye, focalLength, u, v);
			// Finding closest object hit
			HitData hitData;
			hitData.IsHit = false;
			hitData.T = std::numeric_limits<double>::infinity();
			for (const auto& s : world.GetSurfaces()) {
				bool isHit = (*s).IsHit(ray, 0, hitData.T, hitData);
				if (isHit) {
					hitData.HitSurface = s;
					hitData.IntersectingRay = ray;
				}
			}

			// Writing color data to file
			if (hitData.IsHit) {
				// Found closest object, determine shading
				glm::vec3 color = hitData.HitSurface->Color(hitData, world);
				fileWriter << (int)(255 * color.x) << " " << (int)(255 * color.y) << " " << (int)(255 * color.z) << "\n";
			}
			else // TODO: Change normalize function to prevent negative values
				fileWriter << Normalize(u, imageWidth, 255) << " " << Normalize(v, imageHeight, 255) << " 128\n";
		}
	}
	fileWriter.close();

	return true;
}