#pragma once
#include "Bindable.h"

class Blend : public Bindable
{
public:
	Blend(Graphics& gfx, bool state);
	void Bind(Graphics& gfx) noexcept override;
protected:
	Microsoft::WRL::ComPtr<ID3D11BlendState> pBlendState;
};
