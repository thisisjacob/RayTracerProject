#include "RayTracer.h";
#include "WorldState.h"
#include "BaseShader.h"
#include "IdealSpecular.h"
#include "MainInterface.h"
#include "Model.h"
#include <thread>

#include "Application.h"

using std::shared_ptr;
using std::make_shared;
using std::dynamic_pointer_cast;

int main() {
	Application rtApp;
	rtApp.loadTestState();
	rtApp.startApplication();
	return 0;
}
