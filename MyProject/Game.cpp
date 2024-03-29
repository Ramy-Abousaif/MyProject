#include "Game.h"

namespace dx = DirectX;

GDIPlusManager gdipm;

Game::Game()
	:
	wnd(1280, 720, "FPS Game"),
	light(wnd.Gfx())
{
	wnd.Gfx().SetProjection(dx::XMMatrixPerspectiveLH(1.0f, 9.0f / 16.0f, 0.5f, 400.0f));
	SetUpMap();
	gs = GAME_IN_PROGRESS;
}

void Game::DoFrame()
{
	const auto dt = timer.Mark() * speed_factor;
	wnd.Gfx().BeginFrame(0.37f, 0.0f, 0.0f, 1.0f);
	wnd.Gfx().SetCamera(player.cam.GetMatrix());
	light.Bind(wnd.Gfx(), player.cam.GetMatrix());
	ConfineCursor();
	switch (gs)
	{
	case GAME_LOSS:
		game_timer += dt;
		if (game_timer >= 2.0f)
			exit(0);
		break;
	case GAME_WIN:
		game_timer += dt;
		if(game_timer >= 2.0f)
			exit(0);
		break;
	case GAME_IN_PROGRESS:
		//Update and control player
		player.Update(wnd, dt);

		//Render and deal with wall collisions
		player.SetPlayerSpeed(24);
		for (auto& obj : wall)
		{
			obj.get()->Draw(wnd.Gfx());
			player.CheckWalls(wnd, obj.get());
			player.ProjectileCheckWall(wnd, obj.get());
		}

		//Render billboard enemies
		for (auto& obj : enemy)
		{
			if (obj == NULL)
				continue;
			obj.get()->Draw(wnd.Gfx());
			obj.get()->RotateTowards(player.GetPos());
			player.CheckEnemies(wnd, obj.get());
			player.ProjectileCheckEnemy(wnd, obj.get());
			if (obj.get()->GetHealth() <= 0)
			{
				enemy.erase(std::remove(enemy.begin(), enemy.end(), obj), enemy.end());
			}
		}

		if (enemy.size() <= 0)
		{
			gs = GAME_WIN;
		}

		if (player.GetHealth() <= 0)
		{
			gs = GAME_LOSS;
		}
		break;
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

void Game::SetUpMap()
{
	//floor
	for (int i = 0; i < 100; i += 20)
	{
		for (int j = 0; j < 100; j += 20)
		{
			wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(20.0f, 10.0f, 20.0f),
				dx::XMFLOAT3(i, 0.0f, j)));
		}
	}
	//ceiling
	for (int i = 0; i < 100; i += 20)
	{
		for (int j = 0; j < 100; j += 20)
		{
			wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(20.0f, 10.0f, 20.0f),
				dx::XMFLOAT3(i, 30.0f, j)));
		}
	}
	//right wall
	for (int i = 0; i < 100; i += 20)
	{
		wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(10.0f, 20.0f, 20.0f),
			dx::XMFLOAT3(90.0f, 15.0f, i)));
	}
	//left wall
	for (int i = 0; i < 100; i += 20)
	{
		wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(10.0f, 20.0f, 20.0f),
			dx::XMFLOAT3(0.0f, 15.0f, i)));
	}
	//back wall
	for (int i = 0; i < 100; i += 20)
	{
		wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(20.0f, 20.0f, 10.0f),
			dx::XMFLOAT3(i, 15.0f, -15.0f)));
	}
	//front wall
	for (int i = 0; i < 100; i += 20)
	{
		wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(20.0f, 20.0f, 10.0f),
			dx::XMFLOAT3(i, 15.0f, 90.0f)));
	}
	//Pillar
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(10.0f, 10.0f, 10.0f),
		dx::XMFLOAT3(30.0f, 20.0f, 12.0f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(10.0f, 10.0f, 10.0f),
		dx::XMFLOAT3(60.0f, 20.0f, 12.0f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(10.0f, 10.0f, 10.0f),
		dx::XMFLOAT3(30.0f, 10.0f, 12.0f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(10.0f, 10.0f, 10.0f),
		dx::XMFLOAT3(60.0f, 10.0f, 12.0f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(10.0f, 10.0f, 10.0f),
		dx::XMFLOAT3(30.0f, 20.0f, 52.0f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(10.0f, 10.0f, 10.0f),
		dx::XMFLOAT3(60.0f, 20.0f, 52.0f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(10.0f, 10.0f, 10.0f),
		dx::XMFLOAT3(30.0f, 10.0f, 52.0f)));
	wall.push_back(std::make_unique<Wall>(wnd.Gfx(), dx::XMFLOAT3(10.0f, 10.0f, 10.0f),
		dx::XMFLOAT3(60.0f, 10.0f, 52.0f)));

	//enemies
	enemy.push_back(std::make_unique<Enemy>(wnd.Gfx(), dx::XMFLOAT3(2.0f, 5.0f, 1.0f),
		dx::XMFLOAT3(20.0f, 9.0f, 3.0f)));
	enemy.push_back(std::make_unique<Enemy>(wnd.Gfx(), dx::XMFLOAT3(2.0f, 5.0f, 1.0f),
		dx::XMFLOAT3(70.0f, 9.0f, 3.0f)));
	enemy.push_back(std::make_unique<Enemy>(wnd.Gfx(), dx::XMFLOAT3(2.0f, 5.0f, 1.0f),
		dx::XMFLOAT3(45.0f, 9.0f, 13.0f)));
	enemy.push_back(std::make_unique<Enemy>(wnd.Gfx(), dx::XMFLOAT3(2.0f, 5.0f, 1.0f),
		dx::XMFLOAT3(20.0f, 9.0f, 70.0f)));
	enemy.push_back(std::make_unique<Enemy>(wnd.Gfx(), dx::XMFLOAT3(2.0f, 5.0f, 1.0f),
		dx::XMFLOAT3(70.0f, 9.0f, 70.0f)));
	enemy.push_back(std::make_unique<Enemy>(wnd.Gfx(), dx::XMFLOAT3(2.0f, 5.0f, 1.0f),
		dx::XMFLOAT3(45.0f, 9.0f, 60.0f)));
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