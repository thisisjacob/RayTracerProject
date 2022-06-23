#pragma once
#include "RayTracer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"

class MainInterface {
public:
	MainInterface(RayTracer& rayTracer);
	~MainInterface();
	bool startInterface(RayTracer& rayTracer);
private:
	Shader shader;
	GLuint screenVAO, screenVBO, tex;
	GLFWwindow* window;
};
