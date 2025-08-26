#include "Mesh.h"



void Mesh::Initialize(Shader* shader)
{
	this->shader = shader;


	//initialize positions, colors, indices





	CreateBuffers();
}


void Mesh::CreateBuffers()
{
	/*
	_vertexArrayObjectID;
	glGenVertexArrays(1, &_vertexArrayObjectID);
	glBindVertexArray(_vertexArrayObjectID);

	GLuint bufferID;
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	GLuint indexBufferID;
	glGenBuffers(1, &indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLint), indices.data(), GL_STATIC_DRAW);


	const GLchar* attributeName = "positionIn";
	GLuint positionAttributeID = glGetAttribLocation(shader->ProgramID(), attributeName);

	glVertexAttribPointer(positionAttributeID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(positionAttributeID);


	attributeName = "colorIn";
	GLuint colorAttributeID = glGetAttribLocation(shader->ProgramID(), attributeName);

	glVertexAttribPointer(colorAttributeID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(colorAttributeID);



	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	*/
}
