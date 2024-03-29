#include "Shader.h"

Shader::Shader() {
	programId = -1;
	isBuilt = false;
}

unsigned int Shader::GetUniformId(std::string uniformName) {
	if (programId < 0) {
		std::cerr << "Shader.ModifyUniform Failed: Program associated with Shader object not built.\n";
		return -1;
	}
	auto uniformLocation = glGetUniformLocation(programId, uniformName.c_str());
	if (uniformLocation < 0) {
		std::cerr << "Shader.ModifyUniform Failed: Invalid uniform provided. " << uniformName << "\n";
		return -1;
	}
	return uniformLocation;
}

bool Shader::AddShader(std::string filePath, unsigned int shaderType) {
	// No functionality for changing shaders after program is built, so disallow
	if (isBuilt)
		return false;
	// Ensure that shaderType is a valid glEnum of a type of shader
	if (shaderType != GL_VERTEX_SHADER && shaderType != GL_FRAGMENT_SHADER && shaderType != GL_TESS_CONTROL_SHADER && shaderType != GL_TESS_EVALUATION_SHADER && shaderType != GL_GEOMETRY_SHADER && shaderType != GL_COMPUTE_SHADER) {
		std::cerr << "Shader.AddShader Failed: Invalid shaderType specified. Must be an OpenGL shader enum.\n";
		return false;
	}
	// Read from the file
	std::fstream reader;
	std::stringstream buffer;
	reader.open(filePath);
	// Check for reading failure
	if (!reader) {
		std::cerr << "Shader.AddShader Failed: Error when reading shader from file " << filePath << "\n";
		return false;
	}
	buffer << reader.rdbuf();
	// Prepare shader
	unsigned int shader = glCreateShader(shaderType);
	// Save or update Id associated with shader
	shaderTypeIds[shaderType] = shader;
	// Get and compile shader file contents
	std::string shaderString = buffer.str();
	const char* cString = shaderString.c_str();
	reader.close();
	glShaderSource(shader, 1, &cString, NULL);
	glCompileShader(shader);
	// Check for compilation errors
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "Shader.AddShader Failed: Compilation error. " << infoLog << "\n";
		return false;
	}
	return true;
}

bool Shader::BuildProgram() {
	// Must at least have a vertex and fragment shader
	if (shaderTypeIds.find(GL_FRAGMENT_SHADER) == shaderTypeIds.end() || shaderTypeIds.find(GL_VERTEX_SHADER) == shaderTypeIds.end()) {
		std::cerr << "Shader.BuildProgram Failed: No Vertex or Fragment shader compiled.\n";
		return false;
	}
	unsigned int newProgram = glCreateProgram();
	programId = newProgram;
	// Attach all the shaders
	for (auto shaderTypeId : shaderTypeIds) {
		glAttachShader(newProgram, shaderTypeId.second);
	}
	glLinkProgram(newProgram);
	// TODO: Check link validity

	// Deleting compiled shaders
	for (auto shaderTypeId : shaderTypeIds) {
		glDeleteShader(shaderTypeId.second);
	}

	return true;
}

bool Shader::UseProgram() {
	// Check that program is built
	if (programId < 0) {
		std::cerr << "Failed to call Shader::UseProgram. Shader program not built.\n";
		return false;
	}
	glUseProgram(programId);
	//auto err = glGetError();
	auto err = 0;
	// Error checking
	if (err == GL_INVALID_VALUE) {
		std::cerr << "Failed to call Shader::UseProgram. glUseProgram operation returned GL_INVALID_VALUE\n";
		return false;
	}
	else if (err == GL_INVALID_OPERATION) {
		std::cerr << "Failed to call Shader::UseProgram. glUseProgram operation returned GL_INVALID_OPERATION\n";
		return false;
	}

	return true;
}

bool Shader::ModifyUniform(std::string uniformName, int val) {
	unsigned int uniformVal = GetUniformId(uniformName);
	if (uniformVal < 0) return false;
	glUniform1i(uniformVal, val);
	return true;
}

bool Shader::ModifyUniform(std::string uniformName, unsigned int val) {
	unsigned int uniformVal = GetUniformId(uniformName);
	if (uniformVal < 0) return false;
	glUniform1ui(uniformVal, val);
	return true;
}

bool Shader::ModifyUniform(std::string uniformName, float val) {
	unsigned int uniformVal = GetUniformId(uniformName);
	if (uniformVal < 0) return false;
	glUniform1f(uniformVal, val);
	return true;
}
bool Shader::ModifyUniform(std::string uniformName, double val) {
	unsigned int uniformVal = GetUniformId(uniformName);
	if (uniformVal < 0) return false;
	glUniform1d(uniformVal, val);
	return true;
}

bool Shader::ModifyUniform(std::string uniformName, int rows, int cols, const glm::f32* matrix, bool trans) {
	return ModifyUniform(uniformName, rows, cols, matrix, 1, trans);
}

bool Shader::ModifyUniform(std::string uniformName, int rows, int cols, const glm::f32* matrix, int numMatrices, bool trans) {
	unsigned int uniformVal = GetUniformId(uniformName);
	if (uniformVal < 0) return false;
	// Determine which uniform function to use
	auto transEnum = trans ? GL_TRUE : GL_FALSE;
	if (rows == 2 && cols == 2)
		glUniformMatrix2fv(uniformVal, numMatrices, transEnum, matrix);
	else if (rows == 3 && cols == 3)
		glUniformMatrix3fv(uniformVal, numMatrices, transEnum, matrix);
	else if (rows == 4 && cols == 4)
		glUniformMatrix4fv(uniformVal, numMatrices, transEnum, matrix);
	else if (rows == 2 && cols == 3)
		glUniformMatrix2x3fv(uniformVal, numMatrices, transEnum, matrix);
	else if (rows == 3 && cols == 2)
		glUniformMatrix3x2fv(uniformVal, numMatrices, transEnum, matrix);
	else if (rows == 2 && cols == 4)
		glUniformMatrix2x4fv(uniformVal, numMatrices, transEnum, matrix);
	else if (rows == 4 && cols == 2)
		glUniformMatrix4x2fv(uniformVal, numMatrices, transEnum, matrix);
	else if (rows == 3 && cols == 4)
		glUniformMatrix3x4fv(uniformVal, numMatrices, transEnum, matrix);
	else if (rows == 4 && cols == 3)
		glUniformMatrix4x3fv(uniformVal, numMatrices, transEnum, matrix);
	else {
		std::cerr << "Shader::ModifyUniform(std::string, int, int, const glm::f32*) failed. Invalid number of rows and columns provided.";
		return false;
	}
	// TODO: check errors with glGetError()
	return true;
}