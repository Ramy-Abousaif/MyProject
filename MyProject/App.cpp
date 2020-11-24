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
	class Factory
	{
	public:
		Factory(Graphics& gfx)
			:
			gfx(gfx)
		{}
		std::unique_ptr<Drawable> operator()()
		{
			switch (sdist(rng))
			{
			case 0:
				return std::make_unique<SkinnedBox>(
					gfx, rng, adist, ddist,
					odist, rdist
					);
			default:
				assert(false && "impossible drawable option in factory");
				return {};
			}
		}
	private:
		Graphics& gfx;
		std::mt19937 rng{ std::random_device{}() };
		std::uniform_int_distribution<int> sdist{ 0,0 };
		std::uniform_real_distribution<float> adist{ 0.0f,PI * 2.0f };
		std::uniform_real_distribution<float> ddist{ 0.0f,PI * 0.5f };
		std::uniform_real_distribution<float> odist{ 0.0f,PI * 0.08f };
		std::uniform_real_distribution<float> rdist{ 6.0f,20.0f };
	};

	drawables.reserve(nDrawables);
	std::generate_n(std::back_inserter(drawables), nDrawables, Factory{ wnd.Gfx() });

	wnd.Gfx().SetProjection(dx::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
}

void App::DoFrame()
{
	const auto dt = timer.Mark() * speed_factor;
	wnd.Gfx().BeginFrame(0.37f, 0.0f, 0.0f);
	wnd.Gfx().SetCamera(player.cam.GetMatrix());
	light.Bind(wnd.Gfx(), player.cam.GetMatrix());

	for (auto& d : drawables)
	{
		d->Update(wnd.kbd.KeyIsPressed(VK_SPACE) ? 0.0f : dt);
		d->Draw(wnd.Gfx());
	}
	light.Draw(wnd.Gfx());

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

	if (!wnd.CursorEnabled())
	{
		player.Update(wnd, dt);
	}

	while (const auto delta = wnd.mouse.ReadRawDelta())
	{
		if (!wnd.CursorEnabled())
		{
			player.cam.Rotate((float)delta->x, (float)delta->y);
		}
	}

	wnd.Gfx().EndFrame();
}

App::~App()
{}


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
//#include "App.h"
//#include "Box.h"
//#include "Sheet.h"
//#include "SkinnedBox.h"
//#include <memory>
//#include <algorithm>
//#include "MyMath.h"
//#include "Surface.h"
//#include "GDIPlusManager.h"
//
//namespace dx = DirectX;
//
//GDIPlusManager gdipm;
//
//App::App()
//	:
//	wnd(800, 600, "FPS Game")
//{
//	class Factory
//	{
//	public:
//		Factory(Graphics& gfx)
//			:
//			gfx(gfx)
//		{}
//		std::unique_ptr<Drawable> operator()()
//		{
//			switch (typedist(rng))
//			{
//			case 0:
//				return std::make_unique<Sheet>(
//					gfx, rng, adist, ddist,
//					odist, rdist, cdist, ndist,
//					srdist, scdist, sndist
//					);
//			default:
//				assert(false && "bad drawable type in factory");
//				return {};
//			}
//		}
//	private:
//		Graphics& gfx;
//		std::mt19937 rng{ std::random_device{}() };
//		std::uniform_real_distribution<float> adist{ 0.0f,1 };
//		std::uniform_real_distribution<float> ddist{ 0.0f,1 };
//		std::uniform_real_distribution<float> odist{ 0.0f,1 };
//		std::uniform_real_distribution<float> rdist{ -10.0f,10.0f };
//		std::uniform_real_distribution<float> ndist{ 0,0 };
//		std::uniform_real_distribution<float> cdist{ 10, 10 };
//		std::uniform_real_distribution<float> srdist{ 5,5 };
//		std::uniform_real_distribution<float> scdist{ 5,5 };
//		std::uniform_real_distribution<float> sndist{ 5,5 };
//		std::uniform_int_distribution<int> latdist{ 10,20 };
//		std::uniform_int_distribution<int> longdist{ 10,40 };
//		std::uniform_int_distribution<int> typedist{ 0,0 };
//	};
//
//	std::uniform_real_distribution<float> zero{ 0.0f, 0.0f };
//	std::uniform_real_distribution<float> ten{ 10.0f, 10.0f };
//	std::uniform_real_distribution<float> twenty{ 20.0f, 20.0f };
//	std::uniform_real_distribution<float> twentyfive{ 25.0f, 25.0f };
//	std::uniform_real_distribution<float> minustwentyfive{ -25.0f, -25.0f };
//	std::uniform_real_distribution<float> fifty{ 50.0f,50.0f };
//	std::uniform_real_distribution<float> two{ 2.0f,2.0f };
//	std::mt19937 rng{ std::random_device{}() };
//
//	ObjName = std::make_unique<SkinnedBox>(
//		wnd.Gfx(), rng, zero, zero,
//		zero, zero, zero, zero,
//		fifty, two, fifty
//		);
//
//	ObjName1 = std::make_unique<SkinnedBox>(
//		wnd.Gfx(), rng, zero, zero,
//		zero, zero, twenty, twentyfive,
//		fifty, fifty, two
//		);
//
//	ObjName2 = std::make_unique<SkinnedBox>(
//		wnd.Gfx(), rng, zero, zero,
//		zero, zero, twenty, zero,
//		fifty, two, fifty
//		);
//
//	ObjName3 = std::make_unique<SkinnedBox>(
//		wnd.Gfx(), rng, zero, zero,
//		zero, zero, twenty, minustwentyfive,
//		fifty, fifty, two
//		);
//
//	ObjName4 = std::make_unique<SkinnedBox>(
//		wnd.Gfx(), rng, zero, zero,
//		zero, minustwentyfive, twenty, zero,
//		two, fifty, fifty
//		);
//
//	ObjName5 = std::make_unique<SkinnedBox>(
//		wnd.Gfx(), rng, zero, zero,
//		zero, twentyfive, twenty, zero,
//		two, fifty, fifty
//		);
//
//	drawables.reserve(nDrawables);
//	std::generate_n(std::back_inserter(drawables), nDrawables, Factory{ wnd.Gfx() });
//
//	wnd.Gfx().SetProjection(dx::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
//}
//
//void App::DoFrame()
//{
//	const auto dt = timer.Mark();
//	wnd.Gfx().ClearBuffer(0.07f, 0.0f, 0.12f);
//	wnd.Gfx().SetCamera(cam.GetMatrix());
//	for (auto& d : drawables)
//	{
//		d->Update(wnd.kbd.KeyIsPressed(VK_SPACE) ? 0.0f : dt);
//		d->Draw(wnd.Gfx());
//	}
//
//	ObjName->Draw(wnd.Gfx());
//	ObjName1->Draw(wnd.Gfx());
//	ObjName2->Draw(wnd.Gfx());
//	ObjName3->Draw(wnd.Gfx());
//	ObjName4->Draw(wnd.Gfx());
//	ObjName5->Draw(wnd.Gfx());
//
//	while (const auto e = wnd.kbd.ReadKey())
//	{
//		if (!e->IsPress())
//		{
//			continue;
//		}
//
//		switch (e->GetCode())
//		{
//		case VK_ESCAPE:
//			if (wnd.CursorEnabled())
//			{
//				wnd.DisableCursor();
//				wnd.mouse.EnableRaw();
//			}
//			else
//			{
//				wnd.EnableCursor();
//				wnd.mouse.DisableRaw();
//			}
//			break;
//		}
//	}
//
//	if (!wnd.CursorEnabled())
//	{
//		if (wnd.kbd.KeyIsPressed('W'))
//		{
//			cam.Translate({ 0.0f,0.0f,dt });
//		}
//		if (wnd.kbd.KeyIsPressed('A'))
//		{
//			cam.Translate({ -dt,0.0f,0.0f });
//		}
//		if (wnd.kbd.KeyIsPressed('S'))
//		{
//			cam.Translate({ 0.0f,0.0f,-dt });
//		}
//		if (wnd.kbd.KeyIsPressed('D'))
//		{
//			cam.Translate({ dt,0.0f,0.0f });
//		}
//		if (wnd.kbd.KeyIsPressed('R'))
//		{
//			cam.Translate({ 0.0f,dt,0.0f });
//		}
//		if (wnd.kbd.KeyIsPressed('F'))
//		{
//			cam.Translate({ 0.0f,-dt,0.0f });
//		}
//	}
//
//	while (const auto delta = wnd.mouse.ReadRawDelta())
//	{
//		if (!wnd.CursorEnabled())
//		{
//			cam.Rotate((float)delta->x, (float)delta->y);
//		}
//	}
//
//	wnd.Gfx().EndFrame();
//}
//
//App::~App()
//{}
//
//
//int App::Go()
//{
//	while (true)
//	{
//		// process all messages pending, but to not block for new messages
//		if (const auto ecode = Window::ProcessMessages())
//		{
//			// if return optional has value, means we're quitting so return exit code
//			return *ecode;
//		}
//		DoFrame();
//	}
//}