#pragma once
#include "RayTracer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"

class MainInterface {
public:
	MainInterface(const std::vector<glm::vec3>& pixels, int width, int height);
	~MainInterface();
private:
	GLFWwindow* window;
};
