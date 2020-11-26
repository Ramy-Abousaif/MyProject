#pragma once
#include <direct.h>
#include "Window.h"

class Collision
{
public:
	struct Box
	{
		struct 
		{ 
			float min = 0;
			float max = 0;
		} x;
		struct
		{
			float min = 0;
			float max = 0;
		} y;
		struct
		{
			float min = 0;
			float max = 0;
		} z;
	};
	Collision() = default;
	Collision(float width, float height, float depth, float posX, float posY, float posZ);

	bool isOverlapping(DirectX::XMFLOAT3 other);
private:
	Box bindingBox = { 0 };
};

