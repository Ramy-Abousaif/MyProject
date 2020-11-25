#pragma once
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
	Collision(float width, float height, float depth, float posX, float posY, float posZ);

	bool isOverlapping(Box other);
private:
	Box bindingBox = {-0.5f, 0.5f, -0.5f, 0.5f, -0.5f, 0.5f};
};

