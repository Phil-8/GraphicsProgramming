#pragma once




class InputManager
{

public:

	void ProcessInput();

	bool CloseWindow() const { return _quit; }

private:

	bool _quit = false;


};

