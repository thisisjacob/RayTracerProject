#pragma once
#include "WorldState.h"
#include "RayTracer.h"
#include "MainInterface.h"


using std::shared_ptr;
using std::make_shared;
using std::dynamic_pointer_cast;

// Class for encapsulating the ray tracer and interface interactions
class Application {
public:
	Application();
	// Sets the world information of the raytracer
	bool loadState(std::string filePath);
	// Sets the world information of the raytracer
	bool loadState(WorldState worldState);
	// Sets the world information of the raytracer
	bool loadTestState();
	// Starts running the interface and raytraced render
	void startApplication();
private:
	WorldState world;
	RayTracer rt;
};