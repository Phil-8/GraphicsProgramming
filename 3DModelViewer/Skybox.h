#pragma once

#include "Camera.h"
#include "Shader.h"
#include <GL/glew.h>
#include <vector>
#include <string>

class Skybox
{

public:

	Skybox(std::vector<std::string> faces, int width, int height);

	GLuint GenerateCubeMap(std::vector<std::string> faces);

	void Draw(Camera& camera, Shader& shader);


private:

	GLuint _skyboxVAO;
	GLuint _skyboxVBO;
	GLuint _skyboxEBO;
	GLuint _cubeMap;

	int _width;
	int _height;

	static float _vertices[];
	static unsigned int _indices[];

};

