#pragma once
#include "DrawableBase.h"
#include "BindableBase.h"
#include "GraphicsThrowMacros.h"
#include "Cube.h"
#include "Surface.h"
#include "Texture.h"
#include "Sampler.h"
#include "Collision.h"

class Wall : public DrawableBase<Wall>
{
public:
	Wall (Graphics& gfx);
	void Draw(Graphics& gfx, DirectX::FXMMATRIX accumulatedTransform) const noexcept (!IS_DEBUG);
	DirectX::XMMATRIX GetTransformXM() const noexcept override
	{
		return DirectX::XMLoadFloat4x4(&transform);
	}
private:
	mutable DirectX::XMFLOAT4X4 transform;
};