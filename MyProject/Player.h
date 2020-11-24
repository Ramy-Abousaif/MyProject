#pragma once
#include "Camera.h"
#include "Window.h"

class Player
{
public:
	Player();
	~Player();
	void Update(Window& wnd, float dt);
	Camera cam;
	Keyboard kbd;
private:
};

