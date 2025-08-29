#pragma once

#include "Camera.h"
#include "Shader.h"
#include <GL/glew.h>
#include <vector>
#include <string>

class Skybox
{

public:

	Skybox(std::vector<std::string> faces, int width, int height, Shader& shader);

	GLuint GenerateCubeMap(std::vector<std::string> faces);

	void Draw(Camera& camera, Shader& shader);
	void Delete();


private:

	GLuint _vao;
	GLuint _vbo;
	GLuint _ebo;
	GLuint _cubeMap;

	int _width;
	int _height;

	static float _vertices[];
	static unsigned int _indices[];

};

