#include "RayTracer.h"

RayTracer::RayTracer(WorldState world) : image(world.GetCamera().GetImageWidth(), world.GetCamera().GetImageHeight()) {
	this->world = world;
}

RayTracer::RayTracer() {

}

// Calculates a single pixel of the raytraced image, storing the result in the image data
void RayTracer::calculatePixel(int xPixel, int yPixel) {
	const Camera& cam = world.GetCamera();
	Ray ray = Ray(cam.getEye(), cam.getDir(), cam.GetUValue(xPixel), cam.GetVValue(yPixel), cam.GetFocalLength());
	HitData hitData = world.GetIntersection(ray);

	image.pixels[yPixel * cam.GetImageWidth() + xPixel] = getColor(ray, 5, 0);
}

// Calculates rows [startYPixel, endYPixel) of the raytraced image, storing the results in the image data
void RayTracer::calculateRows(int startYPixel, int endYPixel) {
	const Camera& cam = world.GetCamera();
	for (int y = startYPixel; y < endYPixel; y++) {
		calculateRow(y);
		std::cout << "Row: " << y << " Complete\n";
	}
}

// Calculates a row of the raytraced image, storing the results in the image data
void RayTracer::calculateRow(int row) {
	for (int x = 0; x < this->getWidth(); x++) {
		calculatePixel(x, row);
	}
}

// Calculates a column of the raytraced image, storing the results in the image data
void RayTracer::calculateColumn(int column) {
	for (int y = 0; y < this->getHeight(); y++) {
		calculatePixel(column, y);
	}
}

bool RayTracer::Render() {
	const Camera camera = world.GetCamera();
	image.erasePixels();
	int yPos = 0;
	int xPos = 0;
	int i = 0;
	// Get processor concurrency information
	// TODO: Move determination of thread count outside of RayTracer class
	const auto PROCESSOR_COUNT = std::thread::hardware_concurrency() - 1;
	std::cout << "Concurrent Threads Allowed: " << PROCESSOR_COUNT << "\n";
	// Only one thread allowed, or information not available
	// Run without multithreading
	if (PROCESSOR_COUNT <= 1) {
		std::cout << "Multithreading disabled.\n";	
		calculateRows(0, image.getHeight());
	}
	// Multithreading available, so use multithreading
	else {
		std::vector<std::thread> threads;
		// Needs to be double to account for non integer multiples
		const double ROWS_PER_THREAD = camera.GetImageHeight() / static_cast<double>(PROCESSOR_COUNT);
		for (int i = 0; i < PROCESSOR_COUNT; i++) {
			threads.push_back(std::thread(&RayTracer::calculateRows, this, i * ROWS_PER_THREAD, round((i + 1.0) * ROWS_PER_THREAD)));
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
	this->world.GetCamera().resizeImagePlane(newWidth, newHeight);
	image.resizePixels(newWidth, newHeight);
	return true;
}

bool RayTracer::setWorld(const WorldState& newWorld) {
	this->world = newWorld;
	this->refreshImage(world.GetCamera().GetImageWidth(), world.GetCamera().GetImageHeight());
	return true;
}

glm::vec3 RayTracer::getColor(const Ray& ray, const int maxDepth, int currDepth) {
	// Reached max depth, so end the recursion
	if (maxDepth == currDepth) { return glm::vec3(0, 0, 0); }
	HitData hitData = world.GetIntersection(ray);
	// Return resultant color
	if (hitData.IsHit) { 
		return hitData.HitSurface->Color(hitData, world);
	}
	// Return default color
	else { return glm::vec3(0.207, 0.318, 0.361); }
}