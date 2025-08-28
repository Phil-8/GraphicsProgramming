#pragma once

#include <GL/glew.h>
#include <vector>
#include <string>

class Skybox
{

public:

	Skybox(std::vector<std::string> faces);

	GLuint GenerateCubeMap(std::vector<std::string> faces);

	void Draw();

	static float _vertices[];

private:

	GLuint _skyboxVAO;
	GLuint _skyboxVBO;
	GLuint _cubeMap;


};

