#pragma once

#include "Shader.h"
#include <glm/glm.hpp>

class Pyramid
{

public:

	Pyramid(glm::vec3 position, const char* textureFielPath, Shader& shader);

	void Draw(Shader& shader);
	void Delete();

private:

	static GLfloat _vertices[];
	static GLuint _indices[];

	GLuint _vao;
	GLuint _vbo;
	GLuint _ebo;
	GLuint _textureID;

};