#pragma once

#include <GL/glew.h>
#include <string>

class Shader
{

public:

	//constructor
	Shader(std::string vertexFilePath, std::string fragmentFilePath);

	//property
	GLuint GetProgramID() const { return _shaderProgramID; }

	void Activate();
	void Delete();

private:

	GLuint _shaderProgramID;
	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;

	void CompileShader(GLuint shaderID, const char* shaderCode);
	std::string ReadFile(std::string filePath);
};