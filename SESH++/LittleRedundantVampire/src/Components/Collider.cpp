#include <iostream>
#include "Collider.h"

Collider::Collider(Vector2f size, Vector2f position, float pushFactor, bool solid)
{
	collisionBox = new RectangleShape(size);
	collisionBox->setPosition(position);
	collisionBox->setOrigin(size / 2.0f);
	this->pushFactor = new float(std::min(std::max(pushFactor, 0.0f), 1.0f)); //Clamps the pushfactor betwwen 0 and 1.
	this->solid = new bool(solid);
}

Collider::~Collider()
{
	delete collisionBox;
	collisionBox = nullptr;

	delete pushFactor;
	pushFactor = nullptr;

	delete solid;
	solid = nullptr;
}

void Collider::Move(float deltaX, float deltaY)
{
	*this->gameObject->position += Vector2f(deltaX, deltaY);
}

bool Collider::CheckCollision(Collider* other)
{
	Vector2f position = GetPosition();
	Vector2f halfSize = GetHalfsize();

	Vector2f otherPosition = other->GetPosition();
	Vector2f otherHalfSize = other->GetHalfsize();

	float deltaX = otherPosition.x - position.x;
	float deltaY = otherPosition.y - position.y;

	float intersectX = abs(deltaX) - (otherHalfSize.x + halfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + halfSize.y);

	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		onColliding.Notify(*other->gameObject->objectTag);

		//TODO: All this following is related to pushing an object and maybe shouldn't be in this class. 
		if (*solid == true)
		{
			if (intersectX > intersectY)
			{
				if (deltaX > 0.0f)
				{
					Move(intersectX * (1.0f - *pushFactor), 0.0f);
					//cout << "You're colliding with the left side\n";
				}
				else
				{
					Move(-intersectX * (1.0f - *pushFactor), 0.0f);
					//cout << "You're colliding with the right side\n";
				}
			}
			else
			{
				if (deltaY > 0.0f)
				{
					Move(0.0f, intersectY * (1.0f - *pushFactor));
					//cout << "You're colliding with the top\n";
				}
				else
				{
					Move(0.0f, -intersectY * (1.0f - *pushFactor));
					//cout << "You're colliding with the bottom\n";
				}
			}
		}
		return true; //The objects are intersecting = We are colliding)
	}

	return false; //The objects are not intersecting = We are not colliding
}

void Collider::Awake()
{
	onColliding.Attach(this);
}

void Collider::Start()
{
	unordered_map<ComponentTag, Component*>::iterator it;

	for (it = gameObject->components.begin(); it != gameObject->components.end(); it++)
	{
		onColliding.Attach(it->second);
	}
}

void Collider::Update(Time* timePerFrame)
{

}

void Collider::Destroy()
{
}

ComponentTag Collider::ToEnum()
{
	return ComponentTag::COLLIDER;
}
