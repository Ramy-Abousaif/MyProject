#include "Collision.h"


Collision::Collision(float width, float height, float depth, float posX, float posY, float posZ)
{
	bindingBox.x.max = posX + (width / 2);
	bindingBox.x.min = posX - (width / 2);
	bindingBox.y.max = posY + (height / 2);
	bindingBox.y.min = posY - (height / 2);
	bindingBox.z.max = posZ + (depth / 2);
	bindingBox.z.min = posZ - (depth / 2);
}

bool Collision::isOverlapping(DirectX::XMFLOAT3 other)
{
	if ((bindingBox.x.min <= other.x && bindingBox.x.max >= other.x) &&
		(bindingBox.y.min <= other.y && bindingBox.y.max >= other.y) &&
		(bindingBox.z.min <= other.z && bindingBox.z.max >= other.z))
	{
		return true;
	}
	else
	{
		return false;
	}
}
