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
	CheckInputs(wnd);
	cam.Translate({ inputs.x * dt * player_speed, inputs.y * dt * player_speed, inputs.z * dt * player_speed });
}

bool Player::CheckCollisions(Window& wnd, Wall* wall)
{
	return (wall->isOverlapping(GetPos()));
}

void Player::SetPlayerSpeed(float speed)
{
	player_speed = speed;
}

void Player::CheckInputs(Window& wnd)
{
	inputs = { (float)(wnd.kbd.KeyIsPressed('D') - (wnd.kbd.KeyIsPressed('A'))),
		(float)(wnd.kbd.KeyIsPressed('R') - (wnd.kbd.KeyIsPressed('F'))),
		(float)(wnd.kbd.KeyIsPressed('W') - (wnd.kbd.KeyIsPressed('S'))) };

	while (const auto delta = wnd.mouse.ReadRawDelta())
	{
		if (!wnd.CursorEnabled())
		{
			rotation += (float)delta->x;
			cam.Rotate((rotation) * rot_speed);
		}
	}
}

void Player::SetUp()
{
	x = cam.GetPos().x;
	y = cam.GetPos().y;
	z = cam.GetPos().z;
}

float Player::GetSpeed()
{
	return player_speed;
}

DirectX::XMFLOAT3 Player::GetPos()
{
	return DirectX::XMFLOAT3(x, y, z);
}
