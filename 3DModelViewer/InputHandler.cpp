#include "InputHandler.h"


InputHandler::InputHandler() 
{
	keyboardState = SDL_GetKeyboardState(nullptr);
}


void InputHandler::ProcessInput(Camera& camera)
{
	//process keyboard inputs
	if (IsKeyDown(SDL_SCANCODE_W)) camera.Move(EMoveDirection::Forward);
	if (IsKeyDown(SDL_SCANCODE_A)) camera.Move(EMoveDirection::Left);
	if (IsKeyDown(SDL_SCANCODE_S)) camera.Move(EMoveDirection::Backward);
	if (IsKeyDown(SDL_SCANCODE_D)) camera.Move(EMoveDirection::Right);
	if (IsKeyDown(SDL_SCANCODE_SPACE)) camera.Move(EMoveDirection::Up);
	if (IsKeyDown(SDL_SCANCODE_LCTRL)) camera.Move(EMoveDirection::Down);


	//check for application quit
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{

		case SDL_EVENT_QUIT:
			_quit = true;
			break;

		default:
			break;

		}
	}

}


bool InputHandler::IsKeyDown(SDL_Scancode key)
{
	return keyboardState[key];
}


