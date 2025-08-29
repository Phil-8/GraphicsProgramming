#pragma once

#include "Camera.h"
#include <SDL3/SDL.h>

class InputHandler
{

public:

	//constructor
	InputHandler();

	//property
	bool QuitApplication() const { return _quit; }

	void ProcessInput(Camera& camera);
	bool IsKeyDown(SDL_Scancode key);

private:

	//keyboard
	const bool* keyboardState = nullptr;

	//mouse
	bool _initialClick = true;
	bool _rmbDown = false;
	int _lastMouseX = 0;
	int _lastMouseY = 0;

	//application
	bool _quit = false;

};

