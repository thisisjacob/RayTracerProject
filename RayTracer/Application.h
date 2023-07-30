#pragma once
#include "WorldState.h"
#include "RayTracer.h"
#include "MainInterface.h"
#include "BaseShader.h"
#include "IdealSpecular.h"
#include "Model.h"
#include "RefractionShader.h"
#include "WorldConfig.h";

using std::shared_ptr;
using std::make_shared;
using std::dynamic_pointer_cast;

// Class for encapsulating the ray tracer and interface interactions
class Application {
public:
	Application(WorldConfig& worldData);
	// Sets the world information of the raytracer
	bool loadTestState();
	// Starts running the interface and raytraced render
	void startApplication();
private:
	WorldConfig& worldConfig;
	WorldState world;
	RayTracer rt;
};