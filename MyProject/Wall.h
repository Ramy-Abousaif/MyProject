#pragma once
#include "DrawableBase.h"
#include "BindableBase.h"
#include "GraphicsThrowMacros.h"
#include "Cube.h"
#include "Surface.h"
#include "Texture.h"
#include "Sampler.h"

class Wall : public DrawableBase<Wall>
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
	Wall(Graphics& gfx, DirectX::XMFLOAT3 accumulatedScaling, DirectX::XMFLOAT3 accumulatedPosition);
	void Draw(Graphics& gfx) const noexcept (!IS_DEBUG);
	DirectX::XMMATRIX GetTransformXM() const noexcept override
	{
		return DirectX::XMMatrixScaling(scaling.x, scaling.y, scaling.z) *
			DirectX::XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f) *
			DirectX::XMMatrixTranslation(position.x, position.y, position.z);
	}
	bool isOverlapping(DirectX::XMFLOAT3 other);
private:
	mutable DirectX::XMFLOAT3 position;
	mutable DirectX::XMFLOAT3 scaling;
	Box boundingBox;
};