#include "WindowManager.h"
#include "InputHandler.h"
#include "Camera.h"
#include "Shader.h"
#include "Pyramid.h"
#include "Light.h"
#include "Skybox.h"
#include <glm/glm.hpp>
#include <string>

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

int main()
{
	//initialize window
	WindowManager windowManager;
	windowManager.OpenWindow(WINDOW_WIDTH, WINDOW_HEIGHT);

	//initialize input
	InputHandler inputHandler;

	//initialize camera
	glm::vec3 cameraPosition = glm::vec3(0.5f, 1.0f, 5.0f);
	Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT, cameraPosition);

	//initialize shader
	Shader defaultShader("Shader/default_vert.txt", "Shader/default_frag.txt");
	Shader lightShader("Shader/light_vert.txt", "Shader/light_frag.txt");
	Shader skyboxShader("Shader/skybox_vert.txt", "Shader/skybox_frag.txt");

	//initialize pyramid model
	glm::vec3 pyramidPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	Pyramid pyramid(pyramidPosition, "Textures/pyramidTexture.png", defaultShader);

	//initialize light
	glm::vec3 lightPosition = glm::vec3(1.0f, 2.0f, 1.8f);
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	Light lightSource(lightPosition, lightColor, lightShader, defaultShader);

	//initialize skybox
	std::vector<std::string> skyboxFaces =
	{
		"Textures/skybox_right.png",
		"Textures/skybox_left.png",
		"Textures/skybox_top.png",
		"Textures/skybox_bottom.png",
		"Textures/skybox_front.png",
		"Textures/skybox_back.png",
	};
	Skybox skybox(skyboxFaces, WINDOW_WIDTH, WINDOW_HEIGHT, skyboxShader);

	//enable depht testing
	glEnable(GL_DEPTH_TEST);


	//main loop
	while (!inputHandler.QuitApplication())
	{
		inputHandler.ProcessInput(camera);
		camera.UpdateMatrix(defaultShader, lightShader);
		
		windowManager.ClearScreenBuffers(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		pyramid.Draw(defaultShader);
		lightSource.Draw(lightShader);
		skybox.Draw(camera, skyboxShader);

		windowManager.SwapWindow();
	}

	//clean up
	defaultShader.Delete();
	lightShader.Delete();
	skyboxShader.Delete();
	pyramid.Delete();
	lightSource.Delete();
	skybox.Delete();

	windowManager.CloseWindow();

	return 0;
}