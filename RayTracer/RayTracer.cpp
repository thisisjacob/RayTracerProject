#include "RayTracer.h"

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
	// Generate image by projecting rays
	for (auto v : camera.GenerateVComponents()) {
		for (auto u : camera.GenerateUComponents()) {
			Ray ray = Ray(camera.GetEye(), u, v, -camera.GetFocalLength());
			HitData hitData = world.GetIntersection(ray);

			// Writing color data to file
			if (hitData.IsHit) {
				// Found closest object, determine shading and send to file
				glm::tvec3<double> color = hitData.HitSurface->Color(hitData, world);
				fileWriter << (int)(255 * color.x) << " " << (int)(255 * color.y) << " " << (int)(255 * color.z) << "\n";
			}
			else
				fileWriter << "53 81 92\n";
		}
	}
	fileWriter.close();

	return true;
}