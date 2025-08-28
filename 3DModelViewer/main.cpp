
#include "WindowManager.h"
#include "InputManager.h"
#include "Skybox.h"
#include "Shader.h"
#include <vector>
#include <string>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

//skybox
//input -> camera -> movement
//model
//shader
//licht etc.




//int argc, char* argv[]


int main()
{
	WindowManager windowManager;
	InputManager inputManager;



	windowManager.OpenWindow(WINDOW_WIDTH, WINDOW_HEIGHT);

	//-----------------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------
	//testing area

	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
	};

	//shader part

	Shader shaderProgram("default.vert", "default.frag");



	//buffer part

	GLuint vao;
	GLuint vbo;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);




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











	//main loop

	while (!inputManager.WindowShouldClose()) 
	{
		inputManager.ProcessInput();
		//glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		windowManager.ClearScreenBuffers(GL_COLOR_BUFFER_BIT);








		shaderProgram.Activate();

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);




		windowManager.SwapWindow();
	}




	//testing
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	shaderProgram.Delete();


	windowManager.CloseWindow();

	return 0;

}




