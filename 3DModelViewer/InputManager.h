#pragma once




class InputManager
{

public:

	void ProcessInput();
	bool WindowShouldClose() const { return _quit; }

private:

	bool _quit = false;


};

