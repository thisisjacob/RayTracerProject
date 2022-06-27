#include "WorldState.h"

WorldState::WorldState() {
}

bool WorldState::AddSurface(const std::shared_ptr<Surface> surface) {
	surfaces.push_back(surface);
	return true;
}

bool WorldState::AddLight(const std::shared_ptr<Light> light) {
	lights.push_back(light);
	return true;
}

bool WorldState::SetCamera(Camera camera) {
	this->camera = camera;
	return true;
}

std::vector<std::shared_ptr<Surface>> WorldState::GetSurfaces() {
	return surfaces;
}

std::vector<std::shared_ptr<Light>> WorldState::GetLights() {
	return lights;
}

Camera WorldState::GetCamera() const {
	return camera;
}

HitData WorldState::GetIntersection(Ray ray) {
	HitData hitData;
	hitData.IsHit = false;
	hitData.T = std::numeric_limits<float>::infinity();
	hitData.IntersectingRay = ray;
	// Find hit surfaces for current ray
	for (const auto& s : surfaces) {
		hitData = s->IsHit(s, ray, 0, hitData.T, hitData);
	}
	return hitData;
}

HitData WorldState::GetIntersection(Ray ray, float t0) {
	HitData hitData;
	hitData.IsHit = false;
	hitData.T = std::numeric_limits<float>::infinity();
	hitData.IntersectingRay = ray;
	// Find hit surfaces for current ray
	for (const auto& s : surfaces) {
		hitData = s->IsHit(s, ray, t0, hitData.T, hitData);
	}
	return hitData;
}