#include <iostream>
#include "Collider.h"
#include "../GameWorld.h"


Collider::Collider(Vector2f size, Vector2f position, float pushFactor, bool solid)
{
	wall = new VertexArray(LinesStrip, 2);
	(*wall)[0].position.x = position.x - size.x / 1.8f;
	(*wall)[0].position.y = position.y - size.y / 2;

	(*wall)[1].position.y = position.y - size.y / 2;
	(*wall)[1].position.x = position.x + size.x / 1.8f;

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
	
	//TODO: Delete walls right now program crashes if I do the following.
	delete wall;
	wall = nullptr;
}

void Collider::Move(float deltaX, float deltaY)
{
	*this->gameObject->GetPosition() += Vector2f(deltaX, deltaY);
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
		if (std::find(currentCollisions.begin(), currentCollisions.end(), other) == currentCollisions.end())
		{
			currentCollisions.push_back(other);
			other->currentCollisions.push_back(this);
			onColliderDestroyed.Attach(other);
			other->onColliderDestroyed.Attach(this);
		}

		onColliding.Notify(*other->gameObject->GetObjectTag(), "NotDefined");

		Push(Vector2f(deltaX, deltaY), Vector2f(intersectX, intersectY), other);

		return true; //The objects are intersecting = We are colliding)
	}

	return false; //The objects are not intersecting = We are not colliding
}

Vector2f Collider::GetPosition() const
{
	return *gameObject->GetPosition();
}

Vector2f Collider::GetHalfsize() const
{
	return collisionBox->getSize() / 2.0f;
}

void Collider::Push(Vector2f delta, Vector2f intersect, Collider* other)
{
	if (*solid && *other->solid)
	{
		if (intersect.x > intersect.y)
		{
			if (delta.x > 0.0f)
			{
				Move(intersect.x * (1.0f - *pushFactor), 0.0f);
				//cout << "You're colliding with the left side\n";
				onColliding.Notify(*other->gameObject->GetObjectTag(), "Left");
			}
			else
			{
				Move(-intersect.x * (1.0f - *pushFactor), 0.0f);
				//cout << "You're colliding with the right side\n";
				onColliding.Notify(*other->gameObject->GetObjectTag(), "Right");
			}
		}
		else
		{
			if (delta.y > 0.0f)
			{
				Move(0.0f, intersect.y * (1.0f - *pushFactor));
				//cout << "You're colliding with the top\n";
				onColliding.Notify(*other->gameObject->GetObjectTag(), "Top");
			}
			else
			{
				Move(0.0f, -intersect.y * (1.0f - *pushFactor));
				//cout << "You're colliding with the bottom\n";
				onColliding.Notify(*other->gameObject->GetObjectTag(), "Bottom");
			}
		}
	}
}

void Collider::UpdateListOfCurrentCollisions()
{
	for (auto i = currentCollisions.begin(); i != currentCollisions.end();)
	{
		bool isStillColliding = CheckCollision(*i);
		if (!isStillColliding)
		{
			onNoLongerColliding.Notify("NoLongerCollidingWith", *i);
			onColliderDestroyed.Detach(*i);
			i = currentCollisions.erase(i);
		}
		else
		{
			++i;
		}
	}

}

void Collider::Awake()
{
}

void Collider::Start()
{
	unordered_map<ComponentTag, Component*>::iterator it;
	for (it = (*gameObject->GetComponents()).begin(); it != (*gameObject->GetComponents()).end(); it++)
	{
		onColliding.Attach(it->second);
		onNoLongerColliding.Attach(it->second);
	}

	onColliderDestroyed.Attach(GameWorld::GetInstance());
}

void Collider::Update(Time* timePerFrame)
{
	UpdateListOfCurrentCollisions();

	(*wall)[0].position.x = (*gameObject->GetPosition()).x - collisionBox->getSize().x / 1.8f;
	(*wall)[0].position.y = (*gameObject->GetPosition()).y - collisionBox->getSize().y / 2;

	(*wall)[1].position.y = (*gameObject->GetPosition()).y - collisionBox->getSize().y / 2;
	(*wall)[1].position.x = (*gameObject->GetPosition()).x + collisionBox->getSize().x / 1.8f;
}

void Collider::Destroy()
{
	currentCollisions.clear();
	//This Notify must be called before ~Collider to ensure that anything we are colliding with gets notified 
	// that we are about to be deleted, so they can respond to this in time. 
	onColliderDestroyed.Notify("ColliderDestroyed", this);
	Collider::~Collider();
}

ComponentTag Collider::ToEnum()
{
	return ComponentTag::COLLIDER;
}


void Collider::OnNotify(std::string eventName, IListener* sender)
{
	//This is used to ensure that a collider is removed from our list of currentCollisions before the collider is completely
	//delted from the game along with the gameObject it belongs to.
	if (eventName == "ColliderDestroyed")
	{
		for (auto i = currentCollisions.begin(); i != currentCollisions.end();)
		{
			if (*i == sender)
			{
				onColliderDestroyed.Detach(sender);
				i = currentCollisions.erase(i);
			}
			else
			{
				++i;
			}
		}
	}
}

void Collider::AttachToColliderDestroyedEvent(IListener* listener)
{
	onColliderDestroyed.Attach(listener);
}