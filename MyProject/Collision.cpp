#include "Collision.h"



Collision::Collision(float width, float height, float depth, float posX, float posY, float posZ)
{

}

bool Collision::isOverlapping(Box other)
{
	if ((other.x.min >= this->bindingBox.x.min && other.x.max <= this->bindingBox.x.max) &&
		(other.y.min >= this->bindingBox.y.min && other.y.max <= this->bindingBox.y.max) &&
		(other.z.min >= this->bindingBox.z.min && other.z.max <= this->bindingBox.z.max))

	{
		return true;
	}
	else
	{
		return false;
	}
}
