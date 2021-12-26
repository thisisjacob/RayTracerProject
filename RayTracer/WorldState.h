#pragma once
#include "Light.h";
#include "Surface.h";
#include <vector>

// Holds all of the surfaces and lights to be used by the Ray Tracer
class WorldState {
private:
	std::vector<std::shared_ptr<Surface>> surfaces;
	std::vector<std::shared_ptr<Light>> lights;
public:
	WorldState();
	bool AddSurface(std::shared_ptr<Surface> surface);
	bool AddLight(std::shared_ptr<Light> light);
	std::vector<std::shared_ptr<Surface>> GetSurfaces();
	std::vector<std::shared_ptr<Light>> GetLights();
};