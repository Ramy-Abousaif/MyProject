#include "Wall.h"
Wall::Wall(Graphics& gfx)
{
	namespace dx = DirectX;

	if (!IsStaticInitialized())
	{
		struct Vertex
		{
			dx::XMFLOAT3 pos;
			dx::XMFLOAT3 n;
			dx::XMFLOAT2 tc;
		};
		auto model = Cube::MakeIndependentTextured<Vertex>();
		model.SetNormalsIndependentFlat();

		AddStaticBind(std::make_unique<VertexBuffer>(gfx, model.vertices));

		AddStaticBind(std::make_unique<Texture>(gfx, Surface::FromFile("Images\\cube1.png")));

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
}
void Wall::Draw(Graphics& gfx, DirectX::XMFLOAT3 accumulatedScaling, DirectX::XMFLOAT3 accumulatedPosition) const noexcept (!IS_DEBUG)
{
	position = accumulatedPosition;
	scaling = accumulatedScaling;
	DirectX::XMMatrixScaling(accumulatedScaling.x, accumulatedScaling.y, accumulatedScaling.z) *
		DirectX::XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f) *
		DirectX::XMMatrixTranslation(accumulatedPosition.x, accumulatedPosition.y, accumulatedPosition.z);

	boundingBox.x.max = position.x + (scaling.x / 2);
	boundingBox.x.min = position.x - (scaling.x / 2);
	boundingBox.y.max = position.y + (scaling.y / 2);
	boundingBox.y.min = position.y - (scaling.y / 2);
	boundingBox.z.max = position.z + (scaling.z / 2);
	boundingBox.z.min = position.z - (scaling.z / 2);

	Drawable::Draw(gfx);
}

bool Wall::isOverlapping(DirectX::XMFLOAT3 other)
{
	if ((other.x >= boundingBox.x.min && other.x <= boundingBox.x.max) &&
		(other.y >= boundingBox.y.min && other.y <= boundingBox.y.max) &&
		(other.z >= boundingBox.z.min && other.z <= boundingBox.z.max))
	{
		return true;
	}
	else
	{
		return false;
	}
}