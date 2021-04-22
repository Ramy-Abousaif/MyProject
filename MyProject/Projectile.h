#pragma once
#include "DrawableBase.h"
#include "BindableBase.h"
#include "GraphicsThrowMacros.h"
#include "Plane.h"
#include "Surface.h"
#include "Texture.h"
#include "Sampler.h"
#include "Window.h"
#include "Wall.h"
#include "Enemy.h"

class Projectile : public DrawableBase<Projectile>
{
public:
	struct Box
	{
		struct
		{
			float min;
			float max;
		} x;
		struct
		{
			float min;
			float max;
		} y;
		struct
		{
			float min;
			float max;
		} z;
	};
	Projectile(Graphics& gfx, DirectX::XMFLOAT3 accumulatedScaling, DirectX::XMFLOAT3 accumulatedPosition);
	void Draw(Graphics& gfx) const noexcept (!IS_DEBUG);
	void Update(DirectX::XMFLOAT3 player, float rotation, float dt);
	DirectX::XMMATRIX GetTransformXM() const noexcept override
	{
		return DirectX::XMMatrixScaling(scaling.x, scaling.y, scaling.z) *
			DirectX::XMMatrixRotationRollPitchYaw(0, rotY, 0) *
			DirectX::XMMatrixTranslation(position.x, position.y, position.z);
	}
	bool isOverlapping(DirectX::XMFLOAT3 other);
	bool CheckWalls(Window& wnd, Wall* wall);
	bool CheckEnemies(Window& wnd, Enemy* enemy);
	DirectX::XMFLOAT3 GetContactPoint();
	DirectX::XMFLOAT3 GetPos();
private:
	mutable DirectX::XMFLOAT3 position;
	mutable DirectX::XMFLOAT3 scaling;
	float rotY = 0.0f;
	DirectX::XMFLOAT3 contact_point;
	bool entered = false;
	Box boundingBox;
};

