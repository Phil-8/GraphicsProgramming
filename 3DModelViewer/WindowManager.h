#pragma once

#include <SDL3/SDL.h>
#include <GL/glew.h>

class WindowManager
{

public:

	SDL_Window* window;
	SDL_GLContext context;

	void OpenWindow(int width, int height);
	void SwapWindow();
	void ClearScreenBuffers(GLenum bufferTypes);
	void CloseWindow();

private:

	void SetAttributes();
	void CreateWindow(int width, int height);
	void CreateContext();
	void SetBackgroundColor(float r, float g, float b);

};