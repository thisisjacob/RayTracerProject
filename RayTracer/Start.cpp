#include "Application.h"
#include "WorldLoader.h"
#include <filesystem>

int main() {
	std::string filePath = "./example.json";
	WorldLoader loader(filePath);
	if (!loader.isLoaded) {
		std::cerr << "Failed to load scene data." << std::endl;
		return 1;
	}

	Application rtApp(loader.data);
	rtApp.loadTestState();
	rtApp.startApplication();
	return 0;
}
