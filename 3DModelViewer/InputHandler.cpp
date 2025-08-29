#include "InputHandler.h"

InputHandler::InputHandler()
{
	keyboardState = SDL_GetKeyboardState(nullptr);
}


void InputHandler::ProcessInput(Camera& camera)
{
	//handle keyboard inputs
	if (IsKeyDown(SDL_SCANCODE_W)) camera.Move(EMoveDirection::Forward);
	if (IsKeyDown(SDL_SCANCODE_A)) camera.Move(EMoveDirection::Left);
	if (IsKeyDown(SDL_SCANCODE_S)) camera.Move(EMoveDirection::Backward);
	if (IsKeyDown(SDL_SCANCODE_D)) camera.Move(EMoveDirection::Right);
	if (IsKeyDown(SDL_SCANCODE_SPACE)) camera.Move(EMoveDirection::Up);
	if (IsKeyDown(SDL_SCANCODE_LCTRL)) camera.Move(EMoveDirection::Down);

	//handle mouse inputs
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{

		case SDL_EVENT_MOUSE_BUTTON_DOWN:

			if (event.button.button == SDL_BUTTON_RIGHT)
			{
				_rmbDown = true;
				_initialClick = true;
			}
			break;


		case SDL_EVENT_MOUSE_BUTTON_UP:

			if (event.button.button == SDL_BUTTON_RIGHT) _rmbDown = false;
			break;


		case SDL_EVENT_MOUSE_MOTION:

			if (_rmbDown)
			{
				if (_initialClick)
				{
					_lastMouseX = event.motion.x;
					_lastMouseY = event.motion.y;
					_initialClick = false;
				}

				float deltaX = event.motion.x - _lastMouseX;
				float deltaY = _lastMouseY - event.motion.y;

				_lastMouseX = event.motion.x;
				_lastMouseY = event.motion.y;

				camera.ProcessMouse(deltaX, deltaY);
			}
			break;


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