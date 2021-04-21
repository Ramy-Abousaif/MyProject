#pragma once
#include "Window.h"
#include "MyTimer.h"
#include "Player.h"
#include "PointLight.h"
#include <set>
#include <memory>

class Game
{
public:
	Game();
	// master frame / message loop
	int Go();
	~Game();
private:
	void DoFrame();
	void ConfineCursor();
	void SetUpMap();
private:
	Window wnd;
	MyTimer timer;
	Player player;
	float speed_factor = 1.0f;
	PointLight light;
	static constexpr size_t nDrawables = 180;
	std::vector<std::unique_ptr<class Wall>> wall;
	std::vector<std::unique_ptr<class Sheet>> sheet;
};