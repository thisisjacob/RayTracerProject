#pragma once
#include "Light.h";
#include "Surface.h";
#include <vector>


class WorldState {
private:
	std::vector<std::shared_ptr<Surface>> surfaces;
	std::vector<std::shared_ptr<Light>> lights;
public:
	WorldState();
	bool AddSurface(Surface* surface);
	bool AddLight(Light light);
	std::vector<std::shared_ptr<Surface>> GetSurfaces();
	std::vector<std::shared_ptr<Light>> GetLights();
};