#include "Projectile.h"


Projectile::Projectile(Graphics& gfx, DirectX::XMFLOAT3 accumulatedScaling, DirectX::XMFLOAT3 accumulatedPosition, float rotation)
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
		auto model = Plane::MakeSkinned<Vertex>();
		model.vertices[0].tex = { 0.0f,0.0f };
		model.vertices[1].tex = { 1.0f,0.0f };
		model.vertices[2].tex = { 0.0f,1.0f };
		model.vertices[3].tex = { 1.0f,1.0f };
		model.SetNormalsIndependentFlat();

		AddStaticBind(std::make_unique<VertexBuffer>(gfx, model.vertices));

		AddStaticBind(std::make_unique<Texture>(gfx, Surface::FromFile("Images\\Bullet.png")));

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
		DirectX::XMMatrixRotationRollPitchYaw(0, rotY, 0) *
		DirectX::XMMatrixTranslation(accumulatedPosition.x, accumulatedPosition.y, accumulatedPosition.z);

	boundingBox.x.max = position.x + (scaling.x / 2) + 1.0f;
	boundingBox.x.min = position.x - (scaling.x / 2) - 1.0f;
	boundingBox.y.max = position.y + (scaling.y / 2) + 1.0f;
	boundingBox.y.min = position.y - (scaling.y / 2) - 1.0f;
	boundingBox.z.max = position.z + 1.0f;
	boundingBox.z.min = position.z - 1.0f;

	forward = rotation;
}

void Projectile::Update(DirectX::XMFLOAT3 player, float dt)
{
	if ((player.z - position.z) < 0)
	{
		rotY = atan((player.x - position.x) / (player.z - position.z));
	}
	else
	{
		rotY = atan((player.x - position.x) / (player.z - position.z)) + PI;
	}
	position.x += sin(forward) + dt * 1.0f;
	position.z += cos(forward) + dt * 1.0f;
}

void Projectile::Draw(Graphics& gfx) const noexcept (!IS_DEBUG)
{
	Drawable::Draw(gfx);
}

bool Projectile::CheckWalls(Window& wnd, Wall* wall)
{
	return (wall->isOverlapping(GetPos()));
}

bool Projectile::CheckEnemies(Window& wnd, Enemy* enemy)
{
	return (enemy->isOverlapping(GetPos()));
}

bool Projectile::isOverlapping(DirectX::XMFLOAT3 other)
{
	if ((other.x >= boundingBox.x.min && other.x <= boundingBox.x.max) &&
		(other.y >= boundingBox.y.min && other.y <= boundingBox.y.max) &&
		(other.z >= boundingBox.z.min && other.z <= boundingBox.z.max))
	{
		if (!entered)
		{
			contact_point = DirectX::XMFLOAT3(other.x, other.y, other.z);
			entered = true;
		}
		return true;
	}
	else
	{
		entered = false;
		return false;
	}
}

DirectX::XMFLOAT3 Projectile::GetContactPoint()
{
	return contact_point;
}

DirectX::XMFLOAT3 Projectile::GetPos()
{
	return position;
}