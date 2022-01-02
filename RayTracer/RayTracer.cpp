#include "RayTracer.h"
#include "TestMat.h"
#include "FixedColor.h"
#include "Lambertian.h"

RayTracer::RayTracer(WorldState world) {
	this->world = world;
}

bool RayTracer::Render() {
	std::ofstream fileWriter("test.ppm");
	if (!fileWriter) {
		std::cerr << "Error creating file.\n";
		return false;
	}
	// Image header
	const Camera camera = world.GetCamera();
	fileWriter << "P3\n";
	fileWriter << camera.GetImageWidth() << " " << camera.GetImageHeight() << "\n";
	fileWriter << "255\n";
	// Generate image
	for (auto v : camera.GenerateVComponents()) {
		for (auto u : camera.GenerateUComponents()) {
			Ray ray = Ray(camera.GetEye(), camera.GetFocalLength(), u, v);
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
				glm::tvec3<double> color = hitData.HitSurface->Color(hitData, world);
				fileWriter << (int)(255 * color.x) << " " << (int)(255 * color.y) << " " << (int)(255 * color.z) << "\n";
			}
			else
				fileWriter << (int)(255 * abs(u)) << " " << (int)(255 * abs(v)) << " 128\n";
		}
	}
	fileWriter.close();

	return true;
}