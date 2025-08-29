#pragma once

#include "Shader.h"
#include <glm/glm.hpp>

class Light
{

public:

	Light(glm::vec3 position, glm::vec4 color, Shader& lightSource, Shader& lightReceiver);

	void Render(Shader& shader);
	void Delete();

private:

	static GLfloat _vertices[];
	static GLuint _indices[];

	GLuint _vao;
	GLuint _vbo;
	GLuint _ebo;

};

