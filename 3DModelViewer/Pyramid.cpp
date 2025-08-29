#include "Pyramid.h"
#include <stb_image.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GLfloat Pyramid::_vertices[] =

{//    COORDINATES       |       COLORS          |  TEX_COORD    |       NOMRALS
	-0.5f, 0.0f,  0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 0.0f,		 0.0f, -1.0f,  0.0f,
	-0.5f, 0.0f, -0.5f,		1.0f, 0.0f, 1.0f,		0.0f, 5.0f,		 0.0f, -1.0f,  0.0f,
	 0.5f, 0.0f, -0.5f,		0.0f, 1.0f, 1.0f,		5.0f, 5.0f,		 0.0f, -1.0f,  0.0f,
	 0.5f, 0.0f,  0.5f,		0.0f, 1.0f, 0.0f,		5.0f, 0.0f,		 0.0f, -1.0f,  0.0f,

	-0.5f, 0.0f,  0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 0.0f,		-0.8f,  0.5f,  0.0f,
	-0.5f, 0.0f, -0.5f,		1.0f, 0.0f, 1.0f,		5.0f, 0.0f,		-0.8f,  0.5f,  0.0f,
	 0.0f, 0.8f,  0.0f,		0.0f, 1.0f, 1.0f,		2.5f, 5.0f,		-0.8f,  0.5f,  0.0f,

	-0.5f, 0.0f, -0.5f,		1.0f, 1.0f, 0.0f,		5.0f, 0.0f,		 0.0f,  0.5f, -0.8f,
	 0.5f, 0.0f, -0.5f,		1.0f, 0.0f, 1.0f,		0.0f, 0.0f,		 0.0f,  0.5f, -0.8f,
	 0.0f, 0.8f,  0.0f,		0.0f, 1.0f, 1.0f,		2.5f, 5.0f,		 0.0f,  0.5f, -0.8f,

	 0.5f, 0.0f, -0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 0.0f,		 0.8f,  0.5f,  0.0f,
	 0.5f, 0.0f,  0.5f,		1.0f, 0.0f, 1.0f,		5.0f, 0.0f,		 0.8f,  0.5f,  0.0f,
	 0.0f, 0.8f,  0.0f,		0.0f, 1.0f, 1.0f,		2.5f, 5.0f,		 0.8f,  0.5f,  0.0f,

	 0.5f, 0.0f,  0.5f,		1.0f, 1.0f, 0.0f,		5.0f, 0.0f,		 0.0f,  0.5f,  0.8f,
	-0.5f, 0.0f,  0.5f,		1.0f, 0.0f, 1.0f,		0.0f, 0.0f,		 0.0f,  0.5f,  0.8f,
	 0.0f, 0.8f,  0.0f,		0.0f, 1.0f, 1.0f,		2.5f, 5.0f,		 0.0f,  0.5f,  0.8f
};


GLuint Pyramid::_indices[] =
{
	 0,  1,  2,
	 0,  2,  3,
	 4,  6,  5,
	 7,  9,  8,
	10, 12, 11,
	13, 15, 14
};


Pyramid::Pyramid(glm::vec3 position, const char* textureFielPath, Shader& shader)
{

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(20.0f), glm::vec3(0, 1, 0));
	model = glm::translate(model, position);

	shader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shader.GetProgramID(), "model"), 1, GL_FALSE, glm::value_ptr(model));


	//buffer objects
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glGenBuffers(1, &_ebo);

	glBindVertexArray(_vao);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices), _indices, GL_STATIC_DRAW);

	//position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//normals
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	//texture

	int width;
	int height;
	int channels;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(textureFielPath, &width, &height, &channels, 0);


	glGenTextures(1, &_textureID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	if (data) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint texUni = glGetUniformLocation(shader.GetProgramID(), "textureSampler");
	shader.Activate();
	glUniform1i(texUni, 0);
}


void Pyramid::Draw(Shader& shader)
{
	shader.Activate();
	glBindTexture(GL_TEXTURE_2D, _textureID);
	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, sizeof(_indices) / sizeof(int), GL_UNSIGNED_INT, 0);
}


void Pyramid::Delete()
{
	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(1, &_vbo);
	glDeleteBuffers(1, &_ebo);
	glDeleteTextures(1, &_textureID);
}