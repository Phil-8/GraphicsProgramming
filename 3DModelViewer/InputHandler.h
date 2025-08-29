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

private:

	//keyboard
	const bool* keyboardState = nullptr;

	//mouse
	bool _initialClick = true;
	bool _rmbDown = false;
	int _lastMouseX = 0;
	int _lastMouseY = 0;

	//application state
	bool _quit = false;

	bool IsKeyDown(SDL_Scancode key);
};