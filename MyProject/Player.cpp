#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
}

void Player::Update(Window& wnd, float dt)
{
	if (wnd.kbd.KeyIsPressed('W'))
	{
		cam.Translate({ 0.0f,0.0f,dt });
	}
	if (wnd.kbd.KeyIsPressed('A'))
	{
		cam.Translate({ -dt,0.0f,0.0f });
	}
	if (wnd.kbd.KeyIsPressed('S'))
	{
		cam.Translate({ 0.0f,0.0f,-dt });
	}
	if (wnd.kbd.KeyIsPressed('D'))
	{
		cam.Translate({ dt,0.0f,0.0f });
	}
	if (wnd.kbd.KeyIsPressed('R'))
	{
		cam.Translate({ 0.0f,dt,0.0f });
	}
	if (wnd.kbd.KeyIsPressed('F'))
	{
		cam.Translate({ 0.0f,-dt,0.0f });
	}
}
