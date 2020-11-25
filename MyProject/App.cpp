#include "App.h"
#include "Box.h"
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
}

void App::DoFrame()
{
	const auto dt = timer.Mark() * speed_factor;
	wnd.Gfx().BeginFrame(0.37f, 0.0f, 0.0f);
	wnd.Gfx().SetCamera(player.cam.GetMatrix());
	light.Bind(wnd.Gfx(), player.cam.GetMatrix());

	//floor
	wall.Draw(wnd.Gfx(), dx::XMMatrixScaling(10, 1, 10) * dx::XMMatrixRotationRollPitchYaw(pos.roll, pos.pitch, pos.yaw) *
		dx::XMMatrixTranslation(0, 7.5f, -5));
	wall.Draw(wnd.Gfx(), dx::XMMatrixScaling(10, 1, 10) * dx::XMMatrixRotationRollPitchYaw(pos.roll, pos.pitch, pos.yaw) *
		dx::XMMatrixTranslation(0, 7.5f, 5));
	//ceiling
	wall.Draw(wnd.Gfx(), dx::XMMatrixScaling(10, 1, 10) * dx::XMMatrixRotationRollPitchYaw(pos.roll, pos.pitch, pos.yaw) *
		dx::XMMatrixTranslation(0, 18.0f, -5));
	wall.Draw(wnd.Gfx(), dx::XMMatrixScaling(10, 1, 10) * dx::XMMatrixRotationRollPitchYaw(pos.roll, pos.pitch, pos.yaw) *
		dx::XMMatrixTranslation(0, 18.0f, 5));
	//right wall
	wall.Draw(wnd.Gfx(), dx::XMMatrixScaling(1, 10, 10) * dx::XMMatrixRotationRollPitchYaw(pos.roll, pos.pitch, pos.yaw) *
		dx::XMMatrixTranslation(5.5f, 12.5f, -5.0f));
	wall.Draw(wnd.Gfx(), dx::XMMatrixScaling(1, 10, 10) * dx::XMMatrixRotationRollPitchYaw(pos.roll, pos.pitch, pos.yaw) *
		dx::XMMatrixTranslation(5.5f, 12.5f, 5.0f));
	//left wall
	wall.Draw(wnd.Gfx(), dx::XMMatrixScaling(1, 10, 10) * dx::XMMatrixRotationRollPitchYaw(pos.roll, pos.pitch, pos.yaw) *
		dx::XMMatrixTranslation(-5.5f, 12.5f, -5.0f));
	wall.Draw(wnd.Gfx(), dx::XMMatrixScaling(1, 10, 10) * dx::XMMatrixRotationRollPitchYaw(pos.roll, pos.pitch, pos.yaw) *
		dx::XMMatrixTranslation(-5.5f, 12.5f, 5.0f));
	//back wall
	wall.Draw(wnd.Gfx(), dx::XMMatrixScaling(10, 10, 1) * dx::XMMatrixRotationRollPitchYaw(pos.roll, pos.pitch, pos.yaw) *
		dx::XMMatrixTranslation(0.0f, 12.5f, -10.5f));
	//front wall
	wall.Draw(wnd.Gfx(), dx::XMMatrixScaling(10, 10, 1) * dx::XMMatrixRotationRollPitchYaw(pos.roll, pos.pitch, pos.yaw) *
		dx::XMMatrixTranslation(0.0f, 12.5f, 10.5f));
	light.Draw(wnd.Gfx());

	ConfineCursor();

	//Player controls/movement
	RotateCam();
	if (!wnd.CursorEnabled())
	{
		player.Update(wnd, dt);
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