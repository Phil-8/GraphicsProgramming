#pragma once

#include <GL/glew.h>
#include <string>


//programm erstellen
//objekte erstellen
//objekte kompilieren
//objekte zum programm hinzufügen
//programm linken
//objekte loslösen und zerstören / programm loslösen und zerstören (optional)

//vertexshader fragmentshader


//buffer erzeugen
//buffer binden
//buffer füllen
//bufferdaten linken
//buffer lösen und zerstören


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

