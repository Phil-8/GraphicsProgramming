#pragma once

#include "Shader.h"
#include <vector>
#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>


class Mesh
{

public:

	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> colors;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> textureCoordinates;
	std::vector<GLuint> indices;

	void Initialize(Shader*);
	void Draw();

private:

	Shader* shader = nullptr;
	GLuint _vertexArrayObjectID;

	void CreateBuffers();

};

