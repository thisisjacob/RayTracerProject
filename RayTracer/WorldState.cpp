#include "WorldState.h"

WorldState::WorldState() {
}

bool WorldState::AddSurface(Surface* surface) {
	surfaces.push_back(std::shared_ptr<Surface>(surface));
	return true;
}

bool WorldState::AddLight(Light light) {
	lights.push_back(std::shared_ptr<Light>(&light));
	return true;
}

std::vector<std::shared_ptr<Surface>> WorldState::GetSurfaces() {
	return surfaces;
}

std::vector<std::shared_ptr<Light>> WorldState::GetLights() {
	return lights;
}