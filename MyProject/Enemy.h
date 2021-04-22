#pragma once
#include "DrawableBase.h"
#include "BindableBase.h"
#include "GraphicsThrowMacros.h"
#include "Plane.h"
#include "Surface.h"
#include "Texture.h"
#include "Sampler.h"

class Enemy : public DrawableBase<Enemy>
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
	Enemy(Graphics& gfx, DirectX::XMFLOAT3 accumulatedScaling, DirectX::XMFLOAT3 accumulatedPosition);
	void Draw(Graphics& gfx) const noexcept (!IS_DEBUG);
	void RotateTowards(DirectX::XMFLOAT3 player);
	DirectX::XMMATRIX GetTransformXM() const noexcept override
	{
		return DirectX::XMMatrixScaling(scaling.x, scaling.y, scaling.z) *
			DirectX::XMMatrixRotationRollPitchYaw(0, rotY, 0) *
			DirectX::XMMatrixTranslation(position.x, position.y, position.z);
	}
	bool isOverlapping(DirectX::XMFLOAT3 other);
	DirectX::XMFLOAT3 GetContactPoint();
	DirectX::XMFLOAT3 GetPos();
	float GetHealth();
	void SetHealth(float h);
private:
	float rotY = 0.0f;
	float health = 2.0f;
	mutable DirectX::XMFLOAT3 position;
	mutable DirectX::XMFLOAT3 scaling;
	DirectX::XMFLOAT3 contact_point;
	bool entered = false;
	Box boundingBox;
};