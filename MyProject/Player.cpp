#include "Player.h"  



Player::Player()
{
}


Player::~Player()
{
}

void Player::Update(Window& wnd, float dt)
{
	if (!wnd.CursorEnabled())
	{
		SetUp();
		CheckInputs(wnd, dt);
		cam.Translate({ movements.x * dt * player_speed, movements.y * dt * player_speed, movements.z * dt * player_speed });
	}
	for (auto& obj : projectile)
	{
		obj.get()->Draw(wnd.Gfx());
		obj.get()->Update(pos, ((rotation * 0.22915f * (PI / 180)) + (2 * PI)), dt * 0.25f);
	}
}

void Player::ProjectileCheckWall(Window& wnd, Wall* wall)
{
	for (auto& obj : projectile)
	{
		if (obj == NULL)
			continue;
		if (obj.get()->CheckWalls(wnd, wall))
		{
			projectile.erase(std::remove(projectile.begin(), projectile.end(), obj), projectile.end());
		}
	}
}

void Player::ProjectileCheckEnemy(Window& wnd, Enemy* enemy)
{
	for (auto& obj : projectile)
	{
		if (obj == NULL)
			continue;
		if (obj.get()->CheckEnemies(wnd, enemy))
		{
			enemy->SetHealth(enemy->GetHealth() - 1);
			projectile.erase(std::remove(projectile.begin(), projectile.end(), obj), projectile.end());
		}
	}
}

bool Player::CheckWalls(Window& wnd, Wall* wall)
{
	return (wall->isOverlapping(GetPos()));
}

bool Player::CheckEnemies(Window& wnd, Enemy* enemy)
{
	return (enemy->isOverlapping(GetPos()));
}

void Player::SetPlayerSpeed(float speed)
{
	player_speed = speed;
}

void Player::CheckInputs(Window& wnd, float dt)
{
	//Keyboard movements
	movements = { (float)(wnd.kbd.KeyIsPressed('D') - (wnd.kbd.KeyIsPressed('A'))),
	(float)(wnd.kbd.KeyIsPressed('R') - (wnd.kbd.KeyIsPressed('F'))),
	(float)(wnd.kbd.KeyIsPressed('W') - (wnd.kbd.KeyIsPressed('S'))) };

	//Mouse Rotation
	while (const auto delta = wnd.mouse.ReadRawDelta())
	{
		rotation += (float)delta->x;
		cam.Rotate((rotation)* rot_speed);
	}

	//Shooting
	if (wnd.mouse.LeftIsPressed())
	{
		if (fire_timer >= fire_rate)
		{
			projectile.push_back(std::make_unique<Projectile>(wnd.Gfx(), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f),
				DirectX::XMFLOAT3(pos)));
			fire_timer = 0.0f;
		}
		else
		{
			fire_timer += dt;
		}
	}
	else
	{
		fire_timer = fire_rate;
	}
}

void Player::SetUp()
{
	pos = { cam.GetPos().x, cam.GetPos().y, cam.GetPos().z };
}

float Player::GetSpeed()
{
	return player_speed;
}

float Player::GetRot()
{
	return rotation;
}

float Player::GetHealth()
{
	return health;
}

DirectX::XMFLOAT3 Player::GetPos()
{
	return pos;
}
