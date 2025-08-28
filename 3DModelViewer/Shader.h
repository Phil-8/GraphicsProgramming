#pragma once

#include <GL/glew.h>
#include <string>


class Shader
{

public:

	GLuint ProgramID() const { return _shaderProgramID; }

	Shader(std::string vertexFilePath, std::string fragmentFilePath);

	void Activate();
	void Delete();

private:

	GLuint _shaderProgramID;
	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;

	void CompileShader(GLuint shaderID, const char* shaderCode);
	std::string ReadFile(std::string filePath);
};

