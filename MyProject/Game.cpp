#include "Game.h"
#include "Sheet.h"
#include "SkinnedBox.h"
#include <memory>
#include <algorithm>
#include "MyMath.h"
#include "Surface.h"
#include "GDIPlusManager.h"

namespace dx = DirectX;

GDIPlusManager gdipm;

Game::Game()
	:
	wnd(1280, 720, "FPS Game"),
	light(wnd.Gfx())
{
	wnd.Gfx().SetProjection(dx::XMMatrixPerspectiveLH(1.0f, 9.0f / 16.0f, 0.5f, 400.0f));
	SetUpMap();
}

void Game::DoFrame()
{
	const auto dt = timer.Mark() * speed_factor;
	wnd.Gfx().BeginFrame(0.37f, 0.0f, 0.0f);
	wnd.Gfx().SetCamera(player.cam.GetMatrix());
	light.Bind(wnd.Gfx(), player.cam.GetMatrix());


	for (auto& obj : wall)
	{
		obj.get()->Draw(wnd.Gfx());
	}

	for (auto& obj : sheet)
	{
		obj.get()->Draw(wnd.Gfx());
		obj.get()->RotateTowards(player.GetPos(), player.GetSpeed() * 0.05f);
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
			dx::XMFLOAT3 pointA = { obj.get()->GetPos().x, 0, obj.get()->GetPos().z };
			dx::XMFLOAT3 pointB = { obj.get()->GetContactPoint().x, 0, obj.get()->GetContactPoint().z };
			float distance = sqrt((pointB.x - pointA.x) * (pointB.x - pointA.x) +
				(pointB.y - pointA.y) * (pointB.y - pointA.y) +
				(pointB.z - pointA.z) * (pointB.z - pointA.z));
			dx::XMFLOAT3 force = dx::XMFLOAT3((pointB.x - pointA.x) / distance, (pointB.y - pointA.y) / distance, (pointB.z - pointA.z) / distance);

			//Add resistive force
			player.AddResistiveForce(force, dt * 1.0f);
		}
	}

	wnd.Gfx().EndFrame();
}

Game::~Game()
{}

void Game::ConfineCursor()
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

void Game::RotateCam()
{
	while (const auto delta = wnd.mouse.ReadRawDelta())
	{
		if (!wnd.CursorEnabled())
		{
			player.cam.Rotate((float)delta->x, (float)delta->y);
		}
	}
}

void Game::SetUpMap()
{
	//floor
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(20.0f, 10.0f, 20.0f),
		dx::XMFLOAT3(0.0f, 0.0f, -10.0f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(20.0f, 10.0f, 20.0f),
		dx::XMFLOAT3(0.0f, 0.0f, 10.0f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(20.0f, 10.0f, 20.0f),
		dx::XMFLOAT3(20.0f, 0.0f, -10.0f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(20.0f, 10.0f, 20.0f),
		dx::XMFLOAT3(-20.0f, 0.0f, 10.0f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(20.0f, 10.0f, 20.0f),
		dx::XMFLOAT3(20.0f, 0.0f, 10.0f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(20.0f, 10.0f, 20.0f),
		dx::XMFLOAT3(-20.0f, 0.0f, -10.0f)));
	//ceiling
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(20.0f, 10.0f, 20.0f),
		dx::XMFLOAT3(0.0f, 30.0f, -10.0f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(20.0f, 10.0f, 20.0f),
		dx::XMFLOAT3(0.0f, 30.0f, 10.0f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(20.0f, 10.0f, 20.0f),
		dx::XMFLOAT3(20.0f, 30.0f, -10.0f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(20.0f, 10.0f, 20.0f),
		dx::XMFLOAT3(-20.0f, 30.0f, 10.0f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(20.0f, 10.0f, 20.0f),
		dx::XMFLOAT3(20.0f, 30.0f, 10.0f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(20.0f, 10.0f, 20.0f),
		dx::XMFLOAT3(-20.0f, 30.0f, -10.0f)));
	//right wall
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(10.0f, 20.0f, 20.0f),
		dx::XMFLOAT3(30.5f, 15.0f, -10.0f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(10.0f, 20.0f, 20.0f),
		dx::XMFLOAT3(30.5f, 15.0f, 10.0f)));
	//left wall
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(10.0f, 20.0f, 20.0f),
		dx::XMFLOAT3(-30.5f, 15.0f, -10.0f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(10.0f, 20.0f, 20.0f),
		dx::XMFLOAT3(-30.5f, 15.0f, 10.0f)));
	//back wall
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(20.0f, 20.0f, 10.0f),
		dx::XMFLOAT3(-20.0f, 15.0f, -25.0f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(20.0f, 20.0f, 10.0f),
		dx::XMFLOAT3(20.0f, 15.0f, -25.0f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(20.0f, 20.0f, 10.0f),
		dx::XMFLOAT3(0.0f, 15.0f, -25.0f)));
	//front wall
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(20.0f, 20.0f, 10.0f),
		dx::XMFLOAT3(-20.0f, 15.0f, 25.0f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(20.0f, 20.0f, 10.0f),
		dx::XMFLOAT3(20.0f, 15.0f, 25.0f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(20.0f, 20.0f, 10.0f),
		dx::XMFLOAT3(0.0f, 15.0f, 25.0f)));
	//Pillar
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(10.0f, 10.0f, 10.0f),
		dx::XMFLOAT3(10.0f, 20.0f, 10.5f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(10.0f, 10.0f, 10.0f),
		dx::XMFLOAT3(-10.0f, 20.0f, 10.5f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(10.0f, 10.0f, 10.0f),
		dx::XMFLOAT3(10.0f, 10.0f, 10.5f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(10.0f, 10.0f, 10.0f),
		dx::XMFLOAT3(-10.0f, 10.0f, 10.5f)));

	sheet.push_back(std::make_unique<Sheet>(wnd.Gfx(), dx::XMFLOAT3(1.0f, 1.0f, 1.0f),
		dx::XMFLOAT3(0.0f, 12.0f, -5.0f)));
	sheet.push_back(std::make_unique<Sheet>(wnd.Gfx(), dx::XMFLOAT3(1.0f, 1.0f, 1.0f),
		dx::XMFLOAT3(5.0f, 12.0f, -5.0f)));
}


int Game::Go()
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