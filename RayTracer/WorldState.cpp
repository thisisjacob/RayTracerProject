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

bool WorldState::SetCamera(Camera& camera) {
	this->camera = camera;
	return true;
}

const std::vector<std::shared_ptr<Surface>> WorldState::GetSurfaces() {
	return surfaces;
}

const std::vector<std::shared_ptr<Light>> WorldState::GetLights() {
	return lights;
}

const Camera WorldState::GetCamera() {
	return camera;
}

HitData WorldState::GetIntersection(Ray ray) {
	HitData hitData;
	hitData.IsHit = false;
	hitData.T = std::numeric_limits<double>::infinity();
	// Find hit surfaces for current ray
	for (const auto& s : surfaces) {
		bool isHit = (*s).IsHit(ray, 0, hitData.T, hitData);
		if (isHit) {
			hitData.HitSurface = s;
			hitData.IntersectingRay = ray;
		}
	}
	return hitData;
}