#include "Shader.h"
#include <fstream>


void Shader::Initialize()
{
	_shaderProgramID = 0;
	_vertexShaderID = 0;
	_fragmentShaderID = 0;


	CreateShaderProgram();
	CreateShaderObjects();
	CompileShaders();
	AttachShaders();
	LinkShaderProgram();
}


void Shader::CreateShaderProgram()
{
	_shaderProgramID = glCreateProgram();
}


void Shader::CreateShaderObjects()
{
	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
}


void Shader::CompileShader(GLuint shaderID, std::string fileName)
{
	const GLchar* finalCode;

	std::string content = ReadFile(fileName);
	finalCode = (const GLchar*)(content.c_str());
	glShaderSource(shaderID, 1, &finalCode, nullptr);
	glCompileShader(shaderID);
}


void Shader::CompileShaders()
{
	//CompileShader(vertexShaderID, vertexName);
	//CompileShader(fragmentShaderID, fragmentName);
}


void Shader::AttachShaders() 
{
	glAttachShader(_shaderProgramID, _vertexShaderID);
	glAttachShader(_shaderProgramID, _fragmentShaderID);
}


void Shader::LinkShaderProgram()
{
	glLinkProgram(_shaderProgramID);
}


void Shader::DetachShaders()
{
	glDetachShader(_shaderProgramID, _vertexShaderID);
	glDetachShader(_shaderProgramID, _fragmentShaderID);
}


void Shader::DestroyShaders()
{
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);
}


void Shader::DestroyProgram()
{
	glDeleteProgram(_shaderProgramID);
}


std::string Shader::ReadFile(std::string fileName)
{
	std::fstream file;
	std::string lineText = "";
	std::string finalString = "";

	file.open(fileName);

	while (!file.eof())
	{
		getline(file, lineText);
		finalString += lineText + '\n';
	}

	file.close();

	return finalString;
}




