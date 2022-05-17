#include "RayTracer.h"

RayTracer::RayTracer(WorldState world) : pixels(world.GetCamera().GetImageHeight() * world.GetCamera().GetImageWidth()) {
	this->world = world;
}

void RayTracer::calculatePixel(const Camera& cam, int xPixel, int yPixel) {
	Ray ray = Ray(cam.GetEye(), cam.GetUValue(xPixel), cam.GetVValue(yPixel), -cam.GetFocalLength());
	HitData hitData = world.GetIntersection(ray);

	// Writing color data to file
	if (hitData.IsHit) {
		// Found closest object, determine shading and send to file
		glm::vec3 color = hitData.HitSurface->Color(hitData, world);
		pixels[yPixel * cam.GetImageWidth() + xPixel] = color;
	}
	else {
		pixels[yPixel * cam.GetImageWidth() + xPixel] = glm::vec3(0.207, 0.318, 0.361);
	}
}

void RayTracer::calculatePixels(const Camera& cam, int startYPixel, int endYPixel) {
	for (int y = startYPixel; y < endYPixel; y++) {
		for (int x = 0; x < cam.GetImageWidth(); x++) {
			calculatePixel(cam, x, y);
		}
	}
}

bool RayTracer::Render() {
	const Camera camera = world.GetCamera();
	int yPos = 0;
	int xPos = 0;
	int i = 0;
	// Get processor concurrency information
	const auto PROCESSOR_COUNT = std::thread::hardware_concurrency();
	std::cout << "Concurrent Threads Allowed: " << PROCESSOR_COUNT << "\n";
	// Only one thread allowed, or information not available
	// Run without multithreading
	if (PROCESSOR_COUNT <= 1) {
		std::cout << "Multithreading disabled.\n";	
		for (int y = 0; y < camera.GetImageHeight(); y++) {
			for (int x = 0; x < camera.GetImageWidth(); x++) {
				calculatePixel(camera, x, y);
			}
		}
	}
	// Multithreading available, so use multithreading
	else {
		std::vector<std::thread> threads;
		const int ROWS_PER_THREAD = camera.GetImageHeight() / PROCESSOR_COUNT;
		for (int i = 0; i < PROCESSOR_COUNT; i++) {
			threads.push_back(std::thread(&RayTracer::calculatePixels, this, std::ref(camera), i * ROWS_PER_THREAD, (i + 1) * ROWS_PER_THREAD));
			std::cout << "Thread Count: " << threads.size() << "\n";
		}
		for (std::thread& thread : threads) { thread.join(); }
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