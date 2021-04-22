#include "Blend.h"

namespace wrl = Microsoft::WRL;

Blend::Blend(Graphics& gfx, bool state)
{
	//Create blend state
	D3D11_BLEND_DESC blendDesc = {};
	auto& rtbd = blendDesc.RenderTarget[0];

	if (state)
	{
		rtbd.BlendEnable = true;
		rtbd.SrcBlend = D3D11_BLEND_SRC_ALPHA;
		rtbd.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		rtbd.BlendOp = D3D11_BLEND_OP_ADD;
		rtbd.SrcBlendAlpha = D3D11_BLEND_ZERO;
		rtbd.DestBlendAlpha = D3D11_BLEND_ZERO;
		rtbd.BlendOpAlpha = D3D11_BLEND_OP_ADD;
		rtbd.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	}
}

void Blend::Bind(Graphics& gfx) noexcept
{
	GetContext(gfx)->OMSetBlendState(pBlendState.Get(), nullptr, 0xFFFFFFFFu);
}