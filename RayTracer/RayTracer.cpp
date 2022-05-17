#include "RayTracer.h"

RayTracer::RayTracer(WorldState world) : pixels(world.GetCamera().GetImageHeight() * world.GetCamera().GetImageWidth()) {
	this->world = world;
}

bool RayTracer::Render() {
	const Camera camera = world.GetCamera();
	int yPos = 0;
	int xPos = 0;
	int i = 0;
	// Generate image by projecting rays
	for (int yPixel = 0; yPixel < camera.GetImageHeight(); yPixel++) {
		for (int xPixel = 0; xPixel < camera.GetImageWidth(); xPixel++) {
			Ray ray = Ray(camera.GetEye(), camera.GetUValue(xPixel), camera.GetVValue(yPixel), -camera.GetFocalLength());
			HitData hitData = world.GetIntersection(ray);

			// Writing color data to file
			if (hitData.IsHit) {
				// Found closest object, determine shading and send to file
				glm::vec3 color = hitData.HitSurface->Color(hitData, world);
				pixels[i] = color;
			}
			else {
				pixels[i] = glm::vec3(0.207, 0.318, 0.361);
			}
			i++;
		}
	}

	return true;
}

const std::vector<glm::vec3>& RayTracer::getPixels() { return pixels; }

int RayTracer::getWidth() {
	return world.GetCamera().GetImageWidth();
}

int RayTracer::getHeight() {
	return world.GetCamera().GetImageHeight();
}