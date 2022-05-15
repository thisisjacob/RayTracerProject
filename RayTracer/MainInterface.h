#pragma once
#include "RayTracer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"

class MainInterface {
public:
	MainInterface(RayTracer rayTracer);
	~MainInterface();
private:
	GLFWwindow* window;
};
