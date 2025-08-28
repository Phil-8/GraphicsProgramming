#include "Shader.h"
#include <fstream>

#include <iostream>
#include <sstream>
#include <vector>

Shader::Shader(std::string vertexFilePath, std::string fragmentFilePath)
{
	_shaderProgramID = glCreateProgram();

	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	CompileShader(_vertexShaderID, ReadFile(vertexFilePath));

	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	CompileShader(_fragmentShaderID, ReadFile(fragmentFilePath));

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


const char* Shader::ReadFile(std::string filePath)
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


	/*if (file)
	{
		std::string contents;
		file.seekg(0, std::ios::end);
		contents.resize(file.tellg());
		file.seekg(0, std::ios::beg);
		file.read(&contents[0], contents.size());
		file.close();
		return contents.c_str();
	}*/

	return finalString.c_str();
}




