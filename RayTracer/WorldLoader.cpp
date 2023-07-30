#include "WorldLoader.h";

WorldLoader::WorldLoader(std::string filePath) : data{} {
	std::ifstream f(filePath);

	if (!f) {
		std::cerr << "Failed to load file at path: " << filePath << std::endl;
		isLoaded = false;
		return;
	}

	jsonData = json::parse(f);
	std::cout << jsonData;
	std::cout << jsonData.at("test");
	validateCameraData();
	if (!validateCameraData()) {
		std::cerr << "Failed to load file at path: " << filePath << ". Camera definition is invalid." << std::endl;
		isLoaded = false;
		return;
	}
	loadCameraData();
	isLoaded = true;
}

bool WorldLoader::validateCameraData() {
	if (!jsonData.contains("camera")) {
		std::cerr << "A camera definition is missing." << std::endl;
		return false;
	}
	if (!jsonData.at("camera").contains("imageWidth")) {
		std::cerr << "A camera.imageWidth definition is missing." << std::endl;
		return false;
	}
	if (!jsonData.at("camera").contains("imageHeight")) {
		std::cerr << "A camera.imageHeight definition is missing." << std::endl;
		return false;
	}
	if (!jsonData.at("camera").at("eyePosition").contains("x")) {
		std::cerr << "A camera.eyePosition.x definition is missing." << std::endl;
		return false;
	}
	if (!jsonData.at("camera").at("eyePosition").contains("y")) {
		std::cerr << "A camera.eyePosition.y definition is missing." << std::endl;
		return false;
	}
	if (!jsonData.at("camera").at("eyePosition").contains("z")) {
		std::cerr << "A camera.eyePosition.z definition is missing." << std::endl;
		return false;
	}
	if (!jsonData.at("camera").at("direction").contains("x")) {
		std::cerr << "A camera.direction.x definition is missing." << std::endl;
		return false;
	}
	if (!jsonData.at("camera").at("direction").contains("y")) {
		std::cerr << "A camera.direction.y definition is missing." << std::endl;
		return false;
	}
	if (!jsonData.at("camera").at("direction").contains("z")) {
		std::cerr << "A camera.direction.z definition is missing." << std::endl;
		return false;
	}

	return true;
}

bool WorldLoader::loadCameraData() {
	data.camera.imageWidth = jsonData.at("camera").at("imageWidth");
	data.camera.imageHeight = jsonData.at("camera").at("imageHeight");
	data.camera.eyePosition.x = jsonData.at("camera").at("eyePosition").at("x");
	data.camera.eyePosition.y = jsonData.at("camera").at("eyePosition").at("y");
	data.camera.eyePosition.z = jsonData.at("camera").at("eyePosition").at("z");
	data.camera.cameraDirection.x = jsonData.at("camera").at("direction").at("x");
	data.camera.cameraDirection.y = jsonData.at("camera").at("direction").at("y");
	data.camera.cameraDirection.z = jsonData.at("camera").at("direction").at("z");
	data.camera.focalLength = jsonData.at("camera").at("focalLength");
	return true;
}