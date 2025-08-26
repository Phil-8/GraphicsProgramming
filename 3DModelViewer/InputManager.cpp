#include "InputManager.h"
#include <SDL3/SDL.h>


void InputManager::ProcessInput()
{
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


