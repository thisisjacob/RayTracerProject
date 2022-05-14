#include "MainInterface.h"

// Defined outside of MainInterface.h due to need to match function signatures
void glfwErrorCallback(int error, const char* description);
void messageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const* message, void const* user_param);


MainInterface::MainInterface(const std::vector<glm::vec3>& pixels, int width, int height) {
	const glm::vec2 renderQuads[] = {
		glm::vec2(-1.0, 1.0), glm::vec2(0.0, 1.0),
		glm::vec2(-1.0, -1.0), glm::vec2(0.0, 0.0),
		glm::vec2(1.0, -1.0), glm::vec2(1.0, 0.0),
		glm::vec2(-1.0, 1.0), glm::vec2(0.0, 1.0),
		glm::vec2(1.0, -1.0), glm::vec2(1.0, 0.0),
		glm::vec2(1.0, 1.0), glm::vec2(1.0, 1.0)
	};

	// Setup callback functions
	glfwSetErrorCallback(glfwErrorCallback);
	// Initialize GLAD/GLFW and window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	window = glfwCreateWindow(800, 600, "Raytracer", NULL, NULL);
	if (!window) {
		std::cerr << "GLFW initialization failed.\n";
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "GLAD initialization failed.\n";
		glfwTerminate();
	}

	// Set GLFW settings
	glViewport(0, 0, 800, 600);
	glDebugMessageCallback(messageCallback, nullptr);

	unsigned int screenVAO, screenVBO;
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

	
	

	unsigned int tex;
	glActiveTexture(GL_TEXTURE0);
	glCreateTextures(GL_TEXTURE_2D, 1, &tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, pixels.data());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	Shader shader;
	shader.AddShader("Vertex.glsl", GL_VERTEX_SHADER);
	shader.AddShader("Fragment.glsl", GL_FRAGMENT_SHADER);
	shader.BuildProgram();
	shader.UseProgram();
	shader.ModifyUniform("screenTexture", 0);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader.UseProgram();

		glBindVertexArray(screenVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

MainInterface::~MainInterface() {
	glfwTerminate();
}

void glfwErrorCallback(int error, const char* description) {
	std::cerr << "Error: " << description << "\n";
}

void messageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const* message, void const* user_param) {
	std::cerr << id << ": " << message << "\n";
}