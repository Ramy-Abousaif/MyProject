#pragma once
#include "Window.h"
#include "MyTimer.h"
#include "Player.h"
#include "PointLight.h"
#include "SkinnedBox.h"
#include "Wall.h"
#include <set>

class App
{
public:
	App();
	// master frame / message loop
	int Go();
	~App();
private:
	void DoFrame();
	void RotateCam();
	void ConfineCursor();
private:
	Window wnd;
	MyTimer timer;
	Player player;
	float speed_factor = 1.0f;
	PointLight light;
	static constexpr size_t nDrawables = 180;
	Wall wall{wnd.Gfx()};
};