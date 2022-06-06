#pragma once

#include "Light.h";
#include "Surface.h";
#include <vector>
#include "Camera.h"
#include <iostream>

// Holds all of the surfaces and lights to be used by the Ray Tracer
// This should be used whenever information about the world is needed
class WorldState {
private:
	std::vector<std::shared_ptr<Surface>> surfaces;
	std::vector<std::shared_ptr<Light>> lights;
	Camera camera;
public:
	WorldState();
	// After these objects have been added to WorldState, they should not be modified outside of WorldState
	bool AddSurface(std::shared_ptr<Surface> surface);
	bool AddLight(std::shared_ptr<Light> light);
	bool SetCamera(Camera& camera);
	std::vector<std::shared_ptr<Surface>> GetSurfaces();
	std::vector<std::shared_ptr<Light>> GetLights();
	Camera GetCamera();
	HitData GetIntersection(Ray ray);
	HitData GetIntersection(Ray ray, float t0);
};