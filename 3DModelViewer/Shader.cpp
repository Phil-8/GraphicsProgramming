#include "Shader.h"
#include <fstream>

//for fredco test
#include <iostream>
#include <vector>


Shader::Shader(std::string vertexFilePath, std::string fragmentFilePath)
{
	_shaderProgramID = glCreateProgram();

	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	CompileShader(_vertexShaderID, ReadFile(vertexFilePath).c_str());

	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	CompileShader(_fragmentShaderID, ReadFile(fragmentFilePath).c_str());

	glAttachShader(_shaderProgramID, _vertexShaderID);
	glAttachShader(_shaderProgramID, _fragmentShaderID);

	glLinkProgram(_shaderProgramID);

	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);
}


void Shader::CompileShader(GLuint shaderID, const char* shaderCode)
{
	glShaderSource(shaderID, 1, &shaderCode, nullptr);
	glCompileShader(shaderID);





	//fredco test code

	GLint success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success); // Check for compilation success

	if (!success)
	{
		GLint logLength;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength); // Get length of error log
		std::vector<char> infoLog(logLength); // Allocate buffer for log
		glGetShaderInfoLog(shaderID, logLength, nullptr, infoLog.data()); // Retrieve log

		std::cerr << "Shader error.. compilation failed! \n" << infoLog.data() << std::endl; // Print the log
	}
}


void Shader::Activate()
{
	glUseProgram(_shaderProgramID);
}


void Shader::Delete()
{
	glDeleteProgram(_shaderProgramID);
}


std::string Shader::ReadFile(std::string filePath)
{
	std::ifstream file;
	std::string lineText = "";
	std::string finalString = "";

	file.open(filePath);

	while (!file.eof())
	{
		getline(file, lineText);
		finalString += lineText + '\n';
	}

	file.close();

	return finalString;
}




