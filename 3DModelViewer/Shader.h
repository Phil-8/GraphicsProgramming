#pragma once

#include <GL/glew.h>
#include <string>


//programm erstellen
//objekte erstellen
//objekte kompilieren
//objekte zum programm hinzuf�gen
//programm linken
//objekte losl�sen und zerst�ren / programm losl�sen und zerst�ren (optional)

//vertexshader fragmentshader


//buffer erzeugen
//buffer binden
//buffer f�llen
//bufferdaten linken
//buffer l�sen und zerst�ren


class Shader
{

public:

	GLuint ProgramID() const { return _shaderProgramID; }

	void Initialize();


private:

	GLuint _shaderProgramID;
	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;

	void CreateShaderProgram();
	void CreateShaderObjects();
	void CompileShader(GLuint, std::string);
	void CompileShaders();
	void AttachShaders();
	void LinkShaderProgram();

	void DetachShaders();
	void DestroyShaders();
	void DestroyProgram();

	std::string ReadFile(std::string fileName);
};

