#include "WindowManager.h"

void WindowManager::OpenWindow(int width, int height)
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

	SetAttributes();
	CreateWindow(width, height);
	CreateContext();
	SetBackgroundColor(0.0f, 0.0f, 0.0f);

	glewInit();
}


void WindowManager::SetAttributes()
{
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
}


void WindowManager::CreateWindow(int width, int height)
{
	window = SDL_CreateWindow("3D Model Viewer", width, height, SDL_WINDOW_OPENGL);
}


void WindowManager::CreateContext()
{
	context = SDL_GL_CreateContext(window);
}


void WindowManager::SetBackgroundColor(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0f);
}


void WindowManager::SwapWindow()
{
	SDL_GL_SwapWindow(window);
}


void WindowManager::ClearScreenBuffers(GLenum bufferTypes)
{
	glClear(bufferTypes);
}


void WindowManager::CloseWindow()
{
	SDL_GL_DestroyContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}