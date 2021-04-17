#pragma once
#include "Camera.h"
#include "Window.h"
#include "Wall.h"

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
	void CheckCollisions(Window& wnd, Wall& wall);
private:
	float player_speed = 2.0f;
	float x = 0;
	float y = 0;
	float z = 0;
};

