#include "Player.h"  



Player::Player()
{
}


Player::~Player()
{
}

void Player::Update(Window& wnd, float dt)
{
	SetUp();
	//if (wall->isOverlapping(GetPos()))
	//{
	//	wnd.SetTitle("True");
	//}
	//else
	//{
	//	wnd.SetTitle("false");
	//}
	if (wnd.kbd.KeyIsPressed('W'))
	{
		cam.Translate({ 0.0f,0.0f,dt * player_speed});
	}
	if (wnd.kbd.KeyIsPressed('A'))
	{
		cam.Translate({ -dt * player_speed,0.0f,0.0f });
	}
	if (wnd.kbd.KeyIsPressed('S'))
	{
		cam.Translate({ 0.0f,0.0f,-dt * player_speed });
	}
	if (wnd.kbd.KeyIsPressed('D'))
	{
		cam.Translate({ dt * player_speed,0.0f,0.0f });
	}
	if (wnd.kbd.KeyIsPressed('R'))
	{
		cam.Translate({ 0.0f,dt * player_speed,0.0f });
	}
	if (wnd.kbd.KeyIsPressed('F'))
	{
		cam.Translate({ 0.0f,-dt * player_speed,0.0f });
	}
}

void Player::SetUp()
{
	x = cam.GetPos().x;
	y = cam.GetPos().y;
	z = cam.GetPos().z;
}

DirectX::XMFLOAT3 Player::GetPos()
{
	return DirectX::XMFLOAT3(x, y, z);
}
