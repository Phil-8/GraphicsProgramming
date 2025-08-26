
#include "WindowManager.h"
#include "InputManager.h"


int main(int argc, char* argv[])
{
	WindowManager windowManager;
	InputManager inputManager;

	windowManager.OpenWindow();


	while (!inputManager.WindowShouldClose()) 
	{
		inputManager.ProcessInput();
		windowManager.SwapWindow();
	}


	windowManager.CloseWindow();

	return 0;

}




