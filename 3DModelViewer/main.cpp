#include "WindowManager.h"
#include "InputHandler.h"
#include "Camera.h"
#include "Skybox.h"
#include "Shader.h"
#include "Pyramid.h"
#include "Light.h"
#include <glm/glm.hpp>
#include <string>

const int WINDOW_WIDTH = 1400;
const int WINDOW_HEIGHT = 1000;

int main()
{
	//initialize window
	WindowManager windowManager;
	windowManager.OpenWindow(WINDOW_WIDTH, WINDOW_HEIGHT);

	//initialize input
	InputHandler inputHandler;

	//initialize camera
	glm::vec3 cameraPosition = glm::vec3(0.0f, 1.0f, 5.0f);
	Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT, cameraPosition);

	//initialize shader
	Shader defaultShader("default.vert", "default.frag");
	Shader lightShader("light.vert", "light.frag");
	Shader skyboxShader("skybox.vert", "skybox.frag");

	//initialize pyramid model
	glm::vec3 pyramidPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	Pyramid pyramid(pyramidPosition, "metal.png", defaultShader);

	//initialize light
	glm::vec3 lightPosition = glm::vec3(1.0f, 2.0f, 1.8f);
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	Light light(lightPosition, lightColor, lightShader, defaultShader);

	//initialize skybox
	std::vector<std::string> skyboxFaces =
	{
		"Skybox/right.png",
		"Skybox/left.png",
		"Skybox/top.png",
		"Skybox/bottom.png",
		"Skybox/front.png",
		"Skybox/back.png",
	};
	Skybox skybox(skyboxFaces, WINDOW_WIDTH, WINDOW_HEIGHT, skyboxShader);

	//enable depht testing
	glEnable(GL_DEPTH_TEST);


	//main loop
	while (!inputHandler.QuitApplication())
	{
		windowManager.ClearScreenBuffers(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		inputHandler.ProcessInput(camera);
		
		camera.UpdateMatrix(defaultShader, lightShader);

		pyramid.Draw(defaultShader);

		light.Render(lightShader);

		skybox.Draw(camera, skyboxShader);

		windowManager.SwapWindow();
	}

	//clean up
	defaultShader.Delete();
	lightShader.Delete();
	skyboxShader.Delete();
	pyramid.Delete();
	light.Delete();
	skybox.Delete();

	windowManager.CloseWindow();

	return 0;
}