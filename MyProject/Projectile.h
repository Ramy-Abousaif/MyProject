#pragma once
#include "DrawableBase.h"
#include "BindableBase.h"
#include "GraphicsThrowMacros.h"
#include "Plane.h"
#include "Surface.h"
#include "Texture.h"
#include "Sampler.h"

class Projectile : public DrawableBase<Projectile>
{
public:
	Projectile(Graphics& gfx, DirectX::XMFLOAT3 accumulatedScaling, DirectX::XMFLOAT3 accumulatedPosition);
	void Draw(Graphics& gfx) const noexcept (!IS_DEBUG);
	void RotateTowards(DirectX::XMFLOAT3 player);
	DirectX::XMMATRIX GetTransformXM() const noexcept override
	{
		return DirectX::XMMatrixScaling(scaling.x, scaling.y, scaling.z) *
			DirectX::XMMatrixRotationRollPitchYaw(0, rotY, 0) *
			DirectX::XMMatrixTranslation(position.x, position.y, position.z);
	}
private:
	mutable DirectX::XMFLOAT3 position;
	mutable DirectX::XMFLOAT3 scaling;
	float rotY = 0.0f;
};

