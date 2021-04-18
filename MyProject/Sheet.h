#pragma once
#include "DrawableBase.h"

class Sheet : public DrawableBase<Sheet>
{
public:
	Sheet(Graphics& gfx, DirectX::XMFLOAT3 accumulatedScaling, DirectX::XMFLOAT3 accumulatedPosition);
	void Draw(Graphics& gfx) const noexcept (!IS_DEBUG);
	void RotateTowards(DirectX::XMFLOAT3 player, float dt);
	DirectX::XMMATRIX GetTransformXM() const noexcept override
	{
		return DirectX::XMMatrixScaling(scaling.x, scaling.y, scaling.z) *
			DirectX::XMMatrixRotationRollPitchYaw(roll, pitch, yaw) *
			DirectX::XMMatrixTranslation(position.x, position.y, position.z);
	}
private:
	mutable DirectX::XMFLOAT3 position;
	mutable DirectX::XMFLOAT3 scaling;
	//rotational
	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
};