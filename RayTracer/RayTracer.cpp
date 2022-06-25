#include "RayTracer.h"

RayTracer::RayTracer(WorldState world) : image(world.GetCamera().GetImageWidth(), world.GetCamera().GetImageHeight()) {
	this->world = world;
}

RayTracer::RayTracer() {

}

void RayTracer::calculatePixel(int xPixel, int yPixel) {
	const Camera& cam = world.GetCamera();
	Ray ray = Ray(cam.GetEye(), cam.GetUValue(xPixel), cam.GetVValue(yPixel), -cam.GetFocalLength());
	HitData hitData = world.GetIntersection(ray);

	// Writing color data to file
	if (hitData.IsHit) {
		// Found closest object, determine shading and send to file
		glm::vec3 color = hitData.HitSurface->Color(hitData, world);
		//std::cout << color.x << " " << color.y << " " << color.z << "\n";
		image.pixels[yPixel * cam.GetImageWidth() + xPixel] = color;
		//pixels[yPixel * cam.GetImageWidth() + xPixel] = hitData.HitSurface->GetIntersectionPoint(hitData);
	}
	else {
		image.pixels[yPixel * cam.GetImageWidth() + xPixel] = glm::vec3(0.207, 0.318, 0.361);
	}
}

void RayTracer::calculatePixels(int startYPixel, int endYPixel) {
	const Camera& cam = world.GetCamera();
	for (int y = startYPixel; y < endYPixel; y++) {
		for (int x = 0; x < cam.GetImageWidth(); x++) {
			calculatePixel(x, y);
		}
		std::cout << "Row: " << y << " Complete\n";
	}
}

void RayTracer::calculateRow(int row) {
	for (int i = 0; i < this->getWidth(); i++) {
		// calculate pixel
	}
}

void RayTracer::calculateColumn(int column) {
	for (int i = 0; i < this->getHeight(); i++) {
		// calculate pixel
	}
}

bool RayTracer::Render() {
	const Camera camera = world.GetCamera();
	image.erasePixels();
	int yPos = 0;
	int xPos = 0;
	int i = 0;
	// Get processor concurrency information
	const auto PROCESSOR_COUNT = std::thread::hardware_concurrency() - 1;
	std::cout << "Concurrent Threads Allowed: " << PROCESSOR_COUNT << "\n";
	// Only one thread allowed, or information not available
	// Run without multithreading
	if (PROCESSOR_COUNT <= 1) {
		std::cout << "Multithreading disabled.\n";	
		for (int y = 0; y < camera.GetImageHeight(); y++) {
			for (int x = 0; x < camera.GetImageWidth(); x++) {
				calculatePixel(x, y);
				std::cout << "x: " << x << " y: " << y << "\n";
			}
		}
	}
	// Multithreading available, so use multithreading
	else {
		std::vector<std::thread> threads;
		const int ROWS_PER_THREAD = camera.GetImageHeight() / PROCESSOR_COUNT;
		for (int i = 0; i < PROCESSOR_COUNT; i++) {
			threads.push_back(std::thread(&RayTracer::calculatePixels, this, i * ROWS_PER_THREAD, (i + 1) * ROWS_PER_THREAD));
			std::cout << "Thread Count: " << threads.size() << "\n";
		}
		for (std::thread& thread : threads) { thread.join(); }
	}
	
	return true;
}

const std::vector<glm::vec3>& RayTracer::getPixels() { return image.pixels; }

int RayTracer::getWidth() {
	return world.GetCamera().GetImageWidth();
}

int RayTracer::getHeight() {
	return world.GetCamera().GetImageHeight();
}

bool RayTracer::refreshImage(int newWidth, int newHeight) {
	this->world.GetCamera().refreshImage(newWidth, newHeight);
	image.resizePixels(newWidth, newHeight);
	return true;
}

bool RayTracer::setWorld(const WorldState& newWorld) {
	this->world = newWorld;
	image.resizePixels(world.GetCamera().GetImageWidth(), world.GetCamera().GetImageHeight());
	return true;
}