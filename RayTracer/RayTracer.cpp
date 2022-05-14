#include "RayTracer.h"

RayTracer::RayTracer(WorldState world) : pixels(world.GetCamera().GetImageHeight() * world.GetCamera().GetImageWidth()) {
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

	int yPos = 0;
	int xPos = 0;
	int i = 0;
	// Generate image by projecting rays
	for (auto v : camera.GenerateVComponents()) {
		for (auto u : camera.GenerateUComponents()) {
			Ray ray = Ray(camera.GetEye(), u, v, -camera.GetFocalLength());
			HitData hitData = world.GetIntersection(ray);

			// Writing color data to file
			if (hitData.IsHit) {
				// Found closest object, determine shading and send to file
				glm::tvec3<double> color = hitData.HitSurface->Color(hitData, world);
				pixels[i] = color;
			}
			else {
				pixels[i] = glm::vec3(0.207, 0.318, 0.361);
			}
			i++;
		}
	}
	fileWriter.close();

	return true;
}

const std::vector<glm::vec3>& RayTracer::getPixels() { return pixels; }