#pragma once

#include <SDL3/SDL.h>
#include <GL/glew.h>


class WindowManager
{

public:

	SDL_Window* window;
	SDL_GLContext context;

	void OpenWindow();
	void SetAttributes();
	void CreateWindow();
	void CreateContext();
	void SwapWindow();
	void SetBackgroundColor(float r, float g, float b);
	void ClearScreenBuffers(GLenum bufferTypes);
	void CloseWindow();

private:

	int _windowWidth = 1000;
	int _windowHeight = 800;
};

