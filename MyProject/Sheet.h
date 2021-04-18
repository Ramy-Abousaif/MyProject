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
			DirectX::XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f) *
			DirectX::XMMatrixTranslation(position.x, position.y, position.z);
	}
private:
	mutable DirectX::XMFLOAT3 position;
	mutable DirectX::XMFLOAT3 scaling;
	// positional
	float r;
	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
	float theta;
	float phi;
	float chi;
	// speed (delta/s)
	float droll;
	float dpitch;
	float dyaw;
	float dtheta;
	float dphi;
	float dchi;
};