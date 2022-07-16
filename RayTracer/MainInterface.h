#pragma once
#include "RayTracer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <thread>
#include <future>
#include "Shader.h"
#include "RTImage.h"
#include "WorldState.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class MainInterface {
public:
	MainInterface(int screenWidth, int screenHeight, RayTracer& rt);
	void startInterface();
private:
	int screenWidth, screenHeight;
	Shader shader;
	GLuint screenVAO, screenVBO, tex;
	GLFWwindow* window;
	ImGuiIO* imguiIO;
	RayTracer& rt;
	glm::vec3 cameraPos;
	glm::vec3 cameraDir;
	void teardown();
	// Startup functions
	bool initializeGLFW();
	bool initializeOpenGLState();
	void initializeInterface();
	void renderWindows();
};

const glm::vec2 renderQuads[] = {
	glm::vec2(-1.0, 1.0), glm::vec2(0.0, 1.0),
	glm::vec2(-1.0, -1.0), glm::vec2(0.0, 0.0),
	glm::vec2(1.0, -1.0), glm::vec2(1.0, 0.0),
	glm::vec2(-1.0, 1.0), glm::vec2(0.0, 1.0),
	glm::vec2(1.0, -1.0), glm::vec2(1.0, 0.0),
	glm::vec2(1.0, 1.0), glm::vec2(1.0, 1.0)
};
