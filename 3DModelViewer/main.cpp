
#include "WindowManager.h"
#include "InputHandler.h"
#include "Camera.h"
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

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 1000;


//(fix skybox)
//(put skybox shader in skybox class?)
//textur austauschen
//skybox austauschen?
//code aufräumen und struktur verbessern
//speed anpassbar?
//world coordinates?



int main()
{
	WindowManager windowManager;

	//initialize window
	windowManager.OpenWindow(WINDOW_WIDTH, WINDOW_HEIGHT);


	InputHandler inputHandler;

	Shader defaultShader("default.vert", "default.frag");

	Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT, glm::vec3(0.0f, 0.5f, 4.0f));




	//-----------------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------
	//testing area

	GLfloat vertices[] =

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


	GLuint indices[] =
	{
		 0,  1,  2,
		 0,  2,  3,
		 4,  6,  5,
		 7,  9,  8,
		10, 12, 11,
		13, 15, 14
	};


	//lighting cube
	GLfloat lightVertices[] =
	{
		-0.1f, -0.1f,  0.1f,
		-0.1f, -0.1f, -0.1f,
		 0.1f, -0.1f, -0.1f,
		 0.1f, -0.1f,  0.1f,
		-0.1f,  0.1f,  0.1f,
		-0.1f,  0.1f, -0.1f,
		 0.1f,  0.1f, -0.1f,
		 0.1f,  0.1f,  0.1f,
	};

	GLuint lightIndices[] =
	{
		0, 1, 2,
		0, 2, 3,
		0, 4, 7,
		0, 7, 3,
		3, 7, 6,
		3, 6, 2,
		2, 6, 5,
		2, 5, 1,
		1, 5, 4,
		1, 4, 0,
		4, 5, 6,
		4, 6, 7
	};


	//light

	Shader lightShader("light.vert", "light.frag");

	GLuint lightVAO;
	GLuint lightVBO;
	GLuint lightEBO;

	glGenVertexArrays(1, &lightVAO);
	glGenBuffers(1, &lightVBO);
	glGenBuffers(1, &lightEBO);

	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lightVertices), lightVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lightEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(lightIndices), lightIndices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);


	glm::vec3 lightPosition = glm::vec3(0.5f, 1.0f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPosition);


	float rotation = 0.0f;
	glm::vec3 pyramidPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);

	pyramidModel = glm::translate(pyramidModel, pyramidPosition);

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ProgramID(), "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ProgramID(), "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);


	defaultShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(defaultShader.ProgramID(), "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(defaultShader.ProgramID(), "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(defaultShader.ProgramID(), "lightPosition"), lightPosition.x, lightPosition.y, lightPosition.z);





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




	//-----------------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------



	//skybox

	std::vector<std::string> skyboxFaces =
	{
		"Skybox/right.png",
		"Skybox/left.png",
		"Skybox/top.png",
		"Skybox/down.png",
		"Skybox/front.png",
		"Skybox/back.png",
	};

	Skybox skybox(skyboxFaces, WINDOW_WIDTH, WINDOW_HEIGHT);

	Shader skyboxShader("skybox.vert", "skybox.frag");

	skyboxShader.Activate();
	glUniform1i(glGetUniformLocation(skyboxShader.ProgramID(), "skybox"), 0);




	


	glEnable(GL_DEPTH_TEST);

	//main loop

	while (!inputHandler.QuitApplication())
	{
		inputHandler.ProcessInput(camera);
		//glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		windowManager.ClearScreenBuffers(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//defaultShader.Activate();




		//testing ----------------------------------------------------------------




		camera.UpdateMatrix(45.0f, 0.1f, 100.0f);
		defaultShader.Activate();


		glUniform3f(glGetUniformLocation(defaultShader.ProgramID(), "cameraPosition"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		camera.Matrix(defaultShader, "cameraMatrix");


		//texture binding & drawing
		glBindTexture(GL_TEXTURE_2D, textureID);
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);


		lightShader.Activate();
		camera.Matrix(lightShader, "cameraMatrix");
		glBindVertexArray(lightVAO);

		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);





		skybox.Draw(camera, skyboxShader);
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




