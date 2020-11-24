#pragma once
#include "Window.h"
#include "MyTimer.h"
#include "Player.h"
#include "PointLight.h"
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
private:
	Window wnd;
	MyTimer timer;
	Player player;
	std::vector<std::unique_ptr<class Drawable>> drawables;
	std::unique_ptr<class Drawable> ObjName;
	float speed_factor = 1.0f;
	PointLight light;
	static constexpr size_t nDrawables = 180;
};
//#pragma once
//#include "Window.h"
//#include "MyTimer.h"
//#include "Camera.h"
//#include <set>
//
//class App
//{
//public:
//	App();
//	// master frame / message loop
//	int Go();
//	~App();
//private:
//	void DoFrame();
//private:
//	Window wnd;
//	MyTimer timer;
//	std::vector<std::unique_ptr<class Drawable>> drawables;
//	std::unique_ptr<class Drawable> ObjName;
//	std::unique_ptr<class Drawable> ObjName1;
//	std::unique_ptr<class Drawable> ObjName2;
//	std::unique_ptr<class Drawable> ObjName3;
//	std::unique_ptr<class Drawable> ObjName4;
//	std::unique_ptr<class Drawable> ObjName5;
//	static constexpr size_t nDrawables = 1;
//	Camera cam;
//};