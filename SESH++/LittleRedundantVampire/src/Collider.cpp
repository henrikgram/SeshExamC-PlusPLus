#include "Collider.h"
#include <iostream>

Collider::Collider(RectangleShape& body) : body(body)
{
	onColliding.Attach(this);
}

Collider::~Collider()
{
}

bool Collider::CheckCollision(const Collider& other, float pushFactor)
{
	Vector2f position = GetPosition();
	Vector2f halfSize = GetHalfsize();

	Vector2f otherPosition = other.GetPosition();
	Vector2f otherHalfSize = other.GetHalfsize();

	float deltaX = otherPosition.x - position.x;
	float deltaY = otherPosition.y - position.y;

	float intersectX = abs(deltaX) - (otherHalfSize.x + halfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + halfSize.y);

	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		onColliding.Notify();

		pushFactor = std::min(std::max(pushFactor, 0.0f), 1.0f); //Clamps the pushposition betwwen 0 and 1.

		if (intersectX > intersectY)
		{
			if (deltaX > 0.0f)
			{
				Move(intersectX * (1.0f - pushFactor), 0.0f);
				other.Move(-intersectX * pushFactor, 0.0f);
			}
			else
			{
				Move(-intersectX * (1.0f - pushFactor), 0.0f);
				other.Move(intersectX * pushFactor, 0.0f);
			}
		}
		else
		{
			if (deltaY > 0.0f)
			{
				Move(0.0f, intersectY * (1.0f - pushFactor));
				other.Move(0.0f, -intersectY * pushFactor);
			}
			else
			{
				Move(0.0f, -intersectY * (1.0f - pushFactor));
				other.Move(0.0f, intersectY * pushFactor);
			}
		}

		return true; //The objects are intersecting = We are colliding)
	}

	return false; //The objects are not intersecting = We are not colliding
}

void Collider::Notify(std::string eventName)
{
	cout << "Oh dear I hit something\n";
}
