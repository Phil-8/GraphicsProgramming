#pragma once

#include "Camera.h"
#include <SDL3/SDL.h>

class InputHandler
{

public:

	InputHandler();

	bool QuitApplication() const { return _quit; }

	void ProcessInput(Camera& camera);

	bool IsKeyDown(SDL_Scancode key);



private:

	const bool* keyboardState = nullptr;

	bool _quit = false;



};

