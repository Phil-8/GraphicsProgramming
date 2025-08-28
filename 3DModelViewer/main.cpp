
#include "WindowManager.h"
#include "InputManager.h"
#include "Skybox.h"
#include "Shader.h"
#include <vector>
#include <string>

//test
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;


//input -> camera -> movement
//skybox
//model importieren
//texturen
//licht



//int argc, char* argv[]


int main()
{
	WindowManager windowManager;

	//initializing window
	windowManager.OpenWindow(WINDOW_WIDTH, WINDOW_HEIGHT);


	InputManager inputManager;

	Shader defaultShader("default.vert", "default.frag");
	//Shader skyboxShader("skybox.vert", "skybox.frag");






	//-----------------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------
	//testing area

	GLfloat vertices[] =
	{
		-0.5f, 0.0f,  0.5f,		1.0f, 1.0f, 0.0f,	0.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,		1.0f, 0.0f, 1.0f,	5.0f, 0.0f,
		 0.5f, 0.0f, -0.5f,		0.0f, 1.0f, 1.0f,	0.0f, 0.0f,
		 0.5f, 0.0f,  0.5f,		0.0f, 1.0f, 0.0f,	5.0f, 0.0f,
		 0.0f, 0.8f,  0.0f,		0.0f, 1.0f, 0.0f,	2.5f, 5.0f,
	};


	GLuint indices[] =
	{
		0, 1, 2,
		0, 2, 3,
		0, 1, 4,
		1, 2, 4,
		2, 3, 4,
		3, 0, 4
	};




	//buffer part

	GLuint vao;
	GLuint vbo;
	GLuint ebo;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//test
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	//endtest

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);




	GLuint uniID = glGetUniformLocation(defaultShader.ProgramID(), "scale");



	//texture

	int width;
	int height;
	int channels;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("schiggy.png", &width, &height, &channels, 0);


	GLuint textureID;
	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	if (data) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint texUni = glGetUniformLocation(defaultShader.ProgramID(), "tex");
	defaultShader.Activate();
	glUniform1i(texUni, 0);



	float rotation = 0.0f;

	//-----------------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------



	//skybox

	std::vector<std::string> skyboxFaces =
	{
		"Skybox/right.png",
		"Skybox/left.png",
		"Skybox/top.png",
		"Skybox/bottom.png",
		"Skybox/front.png",
		"Skybox/back.png",
	};

	Skybox skybox(skyboxFaces);









	glEnable(GL_DEPTH_TEST);

	//main loop

	while (!inputManager.WindowShouldClose())
	{
		inputManager.ProcessInput();
		//glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		windowManager.ClearScreenBuffers(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		defaultShader.Activate();


		//testing ----------------------------------------------------------------

		rotation += 0.2f;


		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
		projection = glm::perspective(glm::radians(45.0f), (float)(WINDOW_WIDTH / WINDOW_HEIGHT), 0.1f, 100.0f);

		int modelLocation = glGetUniformLocation(defaultShader.ProgramID(), "model");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

		int viewLocation = glGetUniformLocation(defaultShader.ProgramID(), "view");
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

		int projectionLocation = glGetUniformLocation(defaultShader.ProgramID(), "projection");
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));









		//scale test
		glUniform1f(uniID, 0.5f);
		//texture test
		glBindTexture(GL_TEXTURE_2D, textureID);


		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);



		//end testing ---------------------------------------------------------------


		windowManager.SwapWindow();
	}




	//testing
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	defaultShader.Delete();


	windowManager.CloseWindow();

	return 0;

}




