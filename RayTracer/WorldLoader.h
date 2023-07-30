#pragma once
#include <fstream>
#include <iostream>
#include "nlohmann/json.hpp";
using json = nlohmann::json;
#include "WorldConfig.h";

class WorldLoader {
private:
	json jsonData;
	bool loadCameraData();
	bool validateCameraData();
public:
	WorldLoader(std::string filePath);
	WorldConfig data;
	bool isLoaded = false;
};