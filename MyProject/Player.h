#pragma once
#include "Camera.h"
#include "Window.h"
#include "Wall.h"
#include "Enemy.h"
#include "Projectile.h"

class Player
{
public:
	Player();
	~Player();
	void Update(Window& wnd, float dt);
	Camera cam;
	Keyboard kbd;
	void SetUp();
	DirectX::XMFLOAT3 GetPos();
	void CheckWalls(Window& wnd, Wall* wall);
	void CheckEnemies(Window& wnd, Enemy* enemy);
	void ProjectileCheckWall(Window& wnd, Wall* wall);
	void ProjectileCheckEnemy(Window& wnd, Enemy* enemy);
	void SetPlayerSpeed(float speed);
	void SetHealth(float h);
	float GetSpeed();
	float GetRot();
	float GetHealth();
private:
	void CheckInputs(Window& wnd, float dt);
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 movements;
	float rotation = 0.0f;
	float rot_speed = 0.004f;
	float player_speed = 24.0f;
	float health = 10.0f;
	bool isDead = false;
	float iFrames = 1.0f;
	float iTimer = 0.0f;
	bool inv = false;
	float fire_timer = 0.0f;
	float fire_rate = 0.5f;
	std::vector<std::unique_ptr<class Projectile>> projectile;
};

