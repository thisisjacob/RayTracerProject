#include "WorldState.h"

WorldState::WorldState() {
}

bool WorldState::AddSurface(std::shared_ptr<Surface> surface) {
	surfaces.push_back(surface);
	return true;
}

bool WorldState::AddLight(std::shared_ptr<Light> light) {
	lights.push_back(light);
	return true;
}

std::vector<std::shared_ptr<Surface>> WorldState::GetSurfaces() {
	return surfaces;
}

std::vector<std::shared_ptr<Light>> WorldState::GetLights() {
	return lights;
}