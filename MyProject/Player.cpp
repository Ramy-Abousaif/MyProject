#include "Player.h"  



Player::Player()
{
}


Player::~Player()
{
}

void Player::Update(Window& wnd, float dt)
{
	if (health <= 0)
		isDead = true;
	else
		isDead = false;

	if (!wnd.CursorEnabled() && !isDead)
	{
		SetUp();
		CheckInputs(wnd, dt);
		cam.Translate({ movements.x * dt * player_speed, movements.y * dt * player_speed, movements.z * dt * player_speed });
	}
	for (auto& obj : projectile)
	{
		obj.get()->Draw(wnd.Gfx());
		obj.get()->Update(pos, dt * 0.25f);
	}

	if (inv)
	{
		iTimer += dt;
		if (iTimer >= iFrames)
		{
			inv = false;
			iTimer = 0.0f;
		}
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

void Player::CheckWalls(Window& wnd, Wall* wall)
{
	if ((wall->isOverlapping(GetPos())))
	{
		SetPlayerSpeed(-50);
	}
}

void Player::CheckEnemies(Window& wnd, Enemy* enemy)
{
	if (enemy->isOverlapping(GetPos()) && !inv)
	{
		SetPlayerSpeed(-50);
		SetHealth(GetHealth() - 1);
		inv = true;
	}
}

void Player::SetPlayerSpeed(float speed)
{
	player_speed = speed;
}

void Player::SetHealth(float h)
{
	health = h;
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
				DirectX::XMFLOAT3(pos), ((rotation * 0.22915f * (PI / 180)) + (2 * PI))));
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
