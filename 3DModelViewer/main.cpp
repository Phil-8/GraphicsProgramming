
#include "WindowManager.h"
#include "InputManager.h"
#include "Shader.h"


int main(int argc, char* argv[])
{
	WindowManager windowManager;
	InputManager inputManager;

	//Shader* vertexShader = new Shader();

	windowManager.OpenWindow();


	while (!inputManager.WindowShouldClose()) 
	{
		inputManager.ProcessInput();

		windowManager.ClearScreenBuffers(GL_COLOR_BUFFER_BIT);
		windowManager.SwapWindow();
	}


	windowManager.CloseWindow();

	return 0;

}




