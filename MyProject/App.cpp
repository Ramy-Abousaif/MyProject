#include "App.h"
#include "Sheet.h"
#include "SkinnedBox.h"
#include <memory>
#include <algorithm>
#include "MyMath.h"
#include "Surface.h"
#include "GDIPlusManager.h"

namespace dx = DirectX;

GDIPlusManager gdipm;

App::App()
	:
	wnd(1280, 720, "FPS Game"),
	light(wnd.Gfx())
{
	wnd.Gfx().SetProjection(dx::XMMatrixPerspectiveLH(1.0f, 9.0f / 16.0f, 0.5f, 400.0f));

	//floor
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(20.0f, 2.0f, 20.0f),
		dx::XMFLOAT3(0.0f, 7.5f, -10.0f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(20.0f, 2.0f, 20.0f),
		dx::XMFLOAT3(0.0f, 7.5f, 10.0f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(20.0f, 2.0f, 20.0f),
		dx::XMFLOAT3(20.0f, 7.5f, -10.0f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(20.0f, 2.0f, 20.0f),
		dx::XMFLOAT3(-20.0f, 7.5f, 10.0f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(20.0f, 2.0f, 20.0f),
		dx::XMFLOAT3(20.0f, 7.5f, 10.0f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(20.0f, 2.0f, 20.0f),
		dx::XMFLOAT3(-20.0f, 7.5f, -10.0f)));
	//ceiling
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(20.0f, 2.0f, 20.0f),
		dx::XMFLOAT3(0.0f, 18.0f, -10.0f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(20.0f, 2.0f, 20.0f),
		dx::XMFLOAT3(0.0f, 18.0f, 10.0f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(20.0f, 2.0f, 20.0f),
		dx::XMFLOAT3(20.0f, 18.0f, -10.0f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(20.0f, 2.0f, 20.0f),
		dx::XMFLOAT3(-20.0f, 18.0f, 10.0f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(20.0f, 2.0f, 20.0f),
		dx::XMFLOAT3(20.0f, 18.0f, 10.0f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(20.0f, 2.0f, 20.0f),
		dx::XMFLOAT3(-20.0f, 18.0f, -10.0f)));
	//right wall
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(2.0f, 20.0f, 20.0f),
		dx::XMFLOAT3(30.5f, 12.5f, -10.0f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(2.0f, 20.0f, 20.0f),
		dx::XMFLOAT3(30.5f, 12.5f, 10.0f)));
	//left wall
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(2.0f, 20.0f, 20.0f),
		dx::XMFLOAT3(-30.5f, 12.5f, -10.0f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(2.0f, 20.0f, 20.0f),
		dx::XMFLOAT3(-30.5f, 12.5f, 10.0f)));
	//back wall
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(20.0f, 20.0f, 2.0f),
		dx::XMFLOAT3(-20.0f, 12.5f, -20.5f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(20.0f, 20.0f, 2.0f),
		dx::XMFLOAT3(20.0f, 12.5f, -20.5f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(20.0f, 20.0f, 2.0f),
		dx::XMFLOAT3(0.0f, 12.5f, -20.5f)));
	//front wall
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(20.0f, 20.0f, 2.0f),
		dx::XMFLOAT3(-20.0f, 12.5f, 20.5f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(20.0f, 20.0f, 2.0f),
		dx::XMFLOAT3(20.0f, 12.5f, 20.5f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(20.0f, 20.0f, 2.0f),
		dx::XMFLOAT3(0.0f, 12.5f, 20.5f)));
	//Pillar
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(10.0f, 10.0f, 10.0f),
		dx::XMFLOAT3(10.0f, 12.5f, 10.5f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(10.0f, 10.0f, 10.0f),
		dx::XMFLOAT3(-10.0f, 12.5f, 10.5f)));
}

void App::DoFrame()
{
	const auto dt = timer.Mark() * speed_factor;
	wnd.Gfx().BeginFrame(0.37f, 0.0f, 0.0f);
	wnd.Gfx().SetCamera(player.cam.GetMatrix());
	light.Bind(wnd.Gfx(), player.cam.GetMatrix());


	for (auto& obj : wall)
	{
		obj.get()->Draw(wnd.Gfx());
	}

	ConfineCursor();

	//Player controls/movement
	RotateCam();
	if (!wnd.CursorEnabled())
	{
		player.Update(wnd, dt);
	}

	for (auto& obj : wall)
	{
		if (player.CheckCollisions(wnd, obj.get()))
		{
			//Add Resistive Force
		}
	}

	wnd.Gfx().EndFrame();
}

App::~App()
{}

void App::ConfineCursor()
{
	while (const auto e = wnd.kbd.ReadKey())
	{
		if (!e->IsPress())
		{
			continue;
		}

		switch (e->GetCode())
		{
		case VK_ESCAPE:
			if (wnd.CursorEnabled())
			{
				wnd.DisableCursor();
				wnd.mouse.EnableRaw();
			}
			else
			{
				wnd.EnableCursor();
				wnd.mouse.DisableRaw();
			}
			break;
		}
	}
}

void App::RotateCam()
{
	while (const auto delta = wnd.mouse.ReadRawDelta())
	{
		if (!wnd.CursorEnabled())
		{
			player.cam.Rotate((float)delta->x, (float)delta->y);
		}
	}
}


int App::Go()
{
	while (true)
	{
		// process all messages pending, but to not block for new messages
		if (const auto ecode = Window::ProcessMessages())
		{
			// if return optional has value, means we're quitting so return exit code
			return *ecode;
		}
		DoFrame();
	}
}