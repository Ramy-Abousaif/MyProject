#include "Sheet.h"
#include "BindableBase.h"
#include "GraphicsThrowMacros.h"
#include "Plane.h"
#include "Surface.h"
#include "Texture.h"
#include "Sampler.h"


Sheet::Sheet(Graphics& gfx, DirectX::XMFLOAT3 accumulatedScaling, DirectX::XMFLOAT3 accumulatedPosition)
{
	namespace dx = DirectX;

	if (!IsStaticInitialized())
	{
		struct Vertex
		{
			dx::XMFLOAT3 pos;
			dx::XMFLOAT3 n;
			dx::XMFLOAT2 tc;
			struct
			{
				float u;
				float v;
			} tex;
		};
		auto model = Plane::Make<Vertex>();
		model.vertices[0].tex = { 0.0f,0.0f };
		model.vertices[1].tex = { 1.0f,0.0f };
		model.vertices[2].tex = { 0.0f,1.0f };
		model.vertices[3].tex = { 1.0f,1.0f };
		model.SetNormalsIndependentFlat();

		AddStaticBind(std::make_unique<VertexBuffer>(gfx, model.vertices));

		AddStaticBind(std::make_unique<Texture>(gfx, Surface::FromFile("Images\\PogChimp1.png")));

		AddStaticBind(std::make_unique<Sampler>(gfx));

		auto pvs = std::make_unique<VertexShader>(gfx, L"TexturedPhongVS.cso");
		auto pvsbc = pvs->GetBytecode();
		AddStaticBind(std::move(pvs));

		AddStaticBind(std::make_unique<PixelShader>(gfx, L"TexturedPhongPS.cso"));

		AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, model.indices));

		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
			{ "Normal",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0 },
			{ "TexCoord",0,DXGI_FORMAT_R32G32_FLOAT,0,24,D3D11_INPUT_PER_VERTEX_DATA,0 },
		};
		AddStaticBind(std::make_unique<InputLayout>(gfx, ied, pvsbc));

		AddStaticBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

		struct PSMaterialConstant
		{
			float specularIntensity = 0.6f;
			float specularPower = 30.0f;
			float padding[2];
		} colorConst;
		AddStaticBind(std::make_unique<PixelConstantBuffer<PSMaterialConstant>>(gfx, colorConst, 1u));
	}
	else
	{
		SetIndexFromStatic();
	}

	AddBind(std::make_unique<TransformCbuf>(gfx, *this));

	position = accumulatedPosition;
	scaling = accumulatedScaling;
	DirectX::XMMatrixScaling(accumulatedScaling.x, accumulatedScaling.y, accumulatedScaling.z) *
		DirectX::XMMatrixRotationRollPitchYaw(0, pitch, 0) *
		DirectX::XMMatrixTranslation(accumulatedPosition.x, accumulatedPosition.y, accumulatedPosition.z);
}

void Sheet::RotateTowards(DirectX::XMFLOAT3 player, float dt)
{
	if ((player.z - position.z) < 0 && (player.x - position.x) < 0)
	{
		pitch = atan((player.x - position.x) / (player.z - position.z));
	}
	else if ((player.z - position.z) < 0 && (player.x - position.x) > 0)
	{
		pitch = atan((player.x - position.x) / (player.z - position.z));
	}
	else
	{
		pitch = atan((player.x - position.x) / (player.z - position.z)) + PI;
	}
}

void Sheet::Draw(Graphics& gfx) const noexcept (!IS_DEBUG)
{
	Drawable::Draw(gfx);
}