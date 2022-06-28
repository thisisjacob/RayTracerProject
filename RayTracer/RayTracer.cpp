#include "RayTracer.h"

RayTracer::RayTracer(WorldState world) : image(world.GetCamera().GetImageWidth(), world.GetCamera().GetImageHeight()) {
	this->world = world;
}

RayTracer::RayTracer() {

}

// Calculates a single pixel of the raytraced image, storing the result in the image data
void RayTracer::calculatePixel(int xPixel, int yPixel) {
	const Camera& cam = world.GetCamera();
	//Ray ray = Ray(cam.getEye(), cam.GetUValue(xPixel), cam.GetVValue(yPixel), -cam.GetFocalLength());
	//Ray ray = Ray(cam.getEye(), cam.getDir(), cam.GetUValue(xPixel), cam.GetVValue(yPixel), -cam.GetFocalLength());
	Ray ray = Ray(cam.getEye(), cam.getDir(), cam.GetUValue(xPixel), cam.GetVValue(yPixel), cam.GetFocalLength());
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

// Clears image, resizes it
bool RayTracer::refreshImage(int newWidth, int newHeight) {
	this->world.GetCamera().resizeImagePlane(newWidth, newHeight);
	image.resizePixels(newWidth, newHeight);
	return true;
}

// Changes the world used to generate the raytraced image, and resets the image data
bool RayTracer::setWorld(const WorldState& newWorld) {
	this->world = newWorld;
	this->refreshImage(world.GetCamera().GetImageWidth(), world.GetCamera().GetImageHeight());
	return true;
}