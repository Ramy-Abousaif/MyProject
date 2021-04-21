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
	bool CheckCollisions(Window& wnd, Wall* wall);
	void SetPlayerSpeed(float speed);
	float GetSpeed();
private:
	void CheckInputs(Window& wnd);
	DirectX::XMFLOAT3 inputs;
	float rotation = 0.0f;
	float rot_speed = 0.004f;
	float player_speed = 24.0f;
	float x = 0;
	float y = 0;
	float z = 0;
};

