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
		currentCollisions.push_back(other);
		onGameObjDestroyed.Attach(other);

		OnColliding(Vector2f(deltaX, deltaY), Vector2f(intersectX, intersectY), other);

		return true; //The objects are intersecting = We are colliding)
	}

	return false; //The objects are not intersecting = We are not colliding
}

void Collider::OnColliding(Vector2f delta, Vector2f intersect, Collider* other)
{
	if (*solid && *other->solid)
	{
		if (intersect.x > intersect.y)
		{
			if (delta.x > 0.0f)
			{
				Move(intersect.x * (1.0f - *pushFactor), 0.0f);
				//cout << "You're colliding with the left side\n";
			}
			else
			{
				Move(-intersect.x * (1.0f - *pushFactor), 0.0f);
				//cout << "You're colliding with the right side\n";
			}
		}
		else
		{
			if (delta.y > 0.0f)
			{
				Move(0.0f, intersect.y * (1.0f - *pushFactor));
				//cout << "You're colliding with the top\n";
			}
			else
			{
				Move(0.0f, -intersect.y * (1.0f - *pushFactor));
				//cout << "You're colliding with the bottom\n";
			}
		}
	}
}

void Collider::OnNoLongerColliding()
{
}

void Collider::Awake()
{
	//onColliding.Attach(this);
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
	currentCollisions.clear();
	onGameObjDestroyed.Notify("GameObject Destroyed", this);
}

ComponentTag Collider::ToEnum()
{
	return ComponentTag::COLLIDER;
}


void Collider::Notify(std::string eventName, IListener* sender)
{
	//TODO: Ensure that this doesn't cause issues if the list does not contain the element. 
	//This should remove all instances of the collider in question
	currentCollisions.remove(dynamic_cast<Collider*>(sender));
}