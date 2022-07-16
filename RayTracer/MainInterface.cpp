#include "MainInterface.h"

// Defined outside of MainInterface.h due to need to match function signatures
void glfwErrorCallback(int error, const char* description);
void messageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const* message, void const* user_param);

// Used to limit the amount of texture updates per render cycle
const double FRAME_RATE = 1;

MainInterface::MainInterface(int screenWidth, int screenHeight, RayTracer& rt) 
	: screenWidth{ screenWidth }, screenHeight{ screenHeight }, rt{rt}
{
	cameraDir = rt.getWorld().GetCamera().getDir();
	cameraPos = rt.getWorld().GetCamera().getEye();
	initializeGLFW();
	initializeInterface();
	initializeOpenGLState();
}

bool MainInterface::initializeGLFW() {
	// Setup callback functions
	glfwSetErrorCallback(glfwErrorCallback);
	// Initialize GLAD/GLFW and window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	window = glfwCreateWindow(screenWidth, screenHeight, "Raytracer", NULL, NULL);
	if (!window) {
		std::cerr << "GLFW initialization failed.\n";
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "GLAD initialization failed.\n";
		glfwTerminate();
		return false;
	}

	return true;
}

bool MainInterface::initializeOpenGLState() {
	// Set GLFW settings
	glViewport(0, 0, screenWidth, screenHeight);
	glDebugMessageCallback(messageCallback, nullptr);

	glCreateBuffers(1, &screenVBO);
	glNamedBufferStorage(screenVBO, sizeof(renderQuads), &renderQuads, GL_DYNAMIC_STORAGE_BIT);

	glCreateVertexArrays(1, &screenVAO);
	glVertexArrayVertexBuffer(screenVAO, 0, screenVBO, 0, 2 * sizeof(glm::vec2));

	glEnableVertexArrayAttrib(screenVAO, 0);
	glEnableVertexArrayAttrib(screenVAO, 1);

	glVertexArrayAttribFormat(screenVAO, 0, 2, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribFormat(screenVAO, 1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2));

	glVertexArrayAttribBinding(screenVAO, 0, 0);
	glVertexArrayAttribBinding(screenVAO, 1, 0);

	shader.AddShader("Vertex.glsl", GL_VERTEX_SHADER);
	shader.AddShader("Fragment.glsl", GL_FRAGMENT_SHADER);
	shader.BuildProgram();
	shader.UseProgram();

	return true;
}

void MainInterface::initializeInterface() {
	// Initialize imgui and get IO context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	imguiIO = &ImGui::GetIO();

	// Setup style
	ImGui::StyleColorsDark();

	// Bind to OpenGL
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");
}

void MainInterface::startInterface() {
	// Activate and initialize screen texture
	glActiveTexture(GL_TEXTURE0);
	glCreateTextures(GL_TEXTURE_2D, 1, &tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, rt.image.getWidth(), rt.image.getHeight(), 0, GL_RGB, GL_FLOAT, rt.image.pixels.data());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	shader.ModifyUniform("screenTexture", 0);

	double currTime = -1;
	double lastTime = glfwGetTime();

	std::future<bool> res = std::async(std::launch::async, &RayTracer::Render, &rt);

	while (!glfwWindowShouldClose(window)) {

		auto resStatus = res.wait_for(std::chrono::seconds(0));
		// Completed, so we run the render again for the next frame
		if (resStatus == std::future_status::ready) {
			std::cout << "new async fired\n";
			res = std::async(std::launch::async, &RayTracer::Render, &rt);
		}
		
		currTime = glfwGetTime();
		// Update texture
		// Limit texture updates to prevent crashes
		if ((currTime - lastTime) >= (1.0 / FRAME_RATE)) { glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, rt.image.getWidth(), rt.image.getHeight(), GL_RGB, GL_FLOAT, rt.image.pixels.data()); }

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader.UseProgram();
		glBindVertexArray(screenVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		renderWindows();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	teardown();
}

void MainInterface::renderWindows() {
	// Start a new ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// Toolbar
	bool window_open = true;
	ImGui::Begin("Main Menu", &window_open, ImGuiWindowFlags_MenuBar);
	// Add menu bar
	if (ImGui::BeginMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("Open...")) { std::cout << "open\n"; }
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
	// Add tabs
	if (ImGui::BeginTabBar("Options")) {
		if (ImGui::BeginTabItem("Camera")) {
			ImGui::InputFloat("Pos X", &cameraPos.x);
			ImGui::InputFloat("Pos Y", &cameraPos.y);
			ImGui::InputFloat("Pos Z", &cameraPos.z);
			ImGui::InputFloat("Dir X", &cameraDir.x);
			ImGui::InputFloat("Dir Y", &cameraDir.y);
			ImGui::InputFloat("Dir Z", &cameraDir.z);
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Test")) {
			ImGui::Text("test 2");
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
	// Allow user to render if there is no render ongoing
	if (ImGui::Button("Update")) {
		// Update camera before starting render
		Camera currCam = rt.getWorld().GetCamera();
		currCam.setEye(cameraPos);
		currCam.setDir(cameraDir);
		rt.getWorld().SetCamera(currCam);
		std::cout << "Render Scene Fired\n";
	}

	ImGui::End();

	// Settings
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void MainInterface::teardown() {
	// Window closed, preform cleanup and end the program
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	glDeleteBuffers(1, &screenVBO);
	glDeleteBuffers(1, &screenVAO);
	glDeleteTextures(1, &tex);
	exit(0);
}

void glfwErrorCallback(int error, const char* description) {
	std::cerr << "Error: " << description << "\n";
}

void messageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const* message, void const* user_param) {
	std::cerr << id << ": " << message << "\n";
}