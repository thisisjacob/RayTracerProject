#pragma once
#include "RayTracer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#include "RTImage.h"

class MainInterface {
public:
	MainInterface(int screenWidth, int screenHeight);
	~MainInterface();
	bool startInterface(RTImage& image);
private:
	Shader shader;
	GLuint screenVAO, screenVBO, tex;
	GLFWwindow* window;
};
