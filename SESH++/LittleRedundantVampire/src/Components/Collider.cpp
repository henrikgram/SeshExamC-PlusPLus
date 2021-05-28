#include <iostream>
#include "Collider.h"
#include "../GameWorld.h"


Collider::Collider(Vector2f size, Vector2f position, float pushFactor, bool solid)
{
	//So a object that contains a collider will be able to cast a shadow
	wall = new VertexArray(LinesStrip, 2);
	(*wall)[0].position.x = position.x - size.x / 1.8f;
	(*wall)[0].position.y = position.y - size.y / 2;

	(*wall)[1].position.y = position.y - size.y / 2;
	(*wall)[1].position.x = position.x + size.x / 1.8f;

	this->size = new Vector2f(size);
	this->pushFactor = new float(std::min(std::max(pushFactor, 0.0f), 1.0f)); //Clamps the pushfactor betwwen 0 and 1.
	this->solid = new bool(solid);
}

Collider::~Collider()
{
	delete size;
	size = nullptr;

	delete pushFactor;
	pushFactor = nullptr;

	delete solid;
	solid = nullptr;

	delete wall;
	wall = nullptr;
}

//TODO: �ndre delta til dif. find ud af om der er andre steder vi bruger delta.
void Collider::Move(float deltaX, float deltaY)
{
	this->gameObject->SetPosition(this->gameObject->GetPosition() + Vector2f(deltaX, deltaY));
}

bool Collider::CheckCollision(Collider* other)
{
	//First we define the position and halfsize of this collider and the other.
	Vector2f position = GetPosition();
	Vector2f halfSize = GetHalfsize();

	Vector2f otherPosition = other->GetPosition();
	Vector2f otherHalfSize = other->GetHalfsize();

	//Then we determine the difference between the positions.
	float difX = otherPosition.x - position.x;
	float difY = otherPosition.y - position.y;

	//Then we find the intersecting values which are absolute value of the difference in position minus the sum of our halfSize and the other colliders halfSize.
	//Using absolute values for the difference means that no matter if the difference is a negative number we will view it as a positive because the difference
	//between them should always be a positive. It doesn't make sense to have a negative difference. Either there is no diff�rence or there is a (positive) difference.
	float intersectX = abs(difX) - (otherHalfSize.x + halfSize.x);
	float intersectY = abs(difY) - (otherHalfSize.y + halfSize.y);

	//If the intersecting values are below zero that means we're intersecting/colliding with an object.
	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		//We check to see �f the object we are colliding with is already on our list of currentCollisions, i.e. if it's one we're already aware of.
		if (std::find(currentCollisions.begin(), currentCollisions.end(), other) == currentCollisions.end())
		{
			//We push the other onto our list of currentCollisions and we push ourselves onto the others list of currentCollisions. This is because not all
			//Colliders are set to run the CheckCollision method in the GameWorld update since this would slow down the program significantly. Walls for example.
			currentCollisions.push_back(other);
			other->currentCollisions.push_back(this);
			//We attach the other to our list of listeners for the onColliderDestroyed event so we can let them know if we are destroyed while they are colliding with us.
			// And vice versa.
			onColliderDestroyed.Attach(other);
			other->onColliderDestroyed.Attach(this);
		}
    //TODO: Seems like side is not used at all  since it's NotDefined. Maybe delete it as a parameter.
		onColliding.Notify(other->gameObject->GetObjectTag(), "NotDefined");

		Push(Vector2f(difX, difY), Vector2f(intersectX, intersectY), other);

		return true; //The objects are intersecting = We are colliding)
	}

	return false; //The objects are not intersecting = We are not colliding
}

Vector2f Collider::GetPosition() const
{
	return gameObject->GetPosition();
}

Vector2f Collider::GetHalfsize() const
{
	Vector2f tmp(size->x / 2, size->y / 2);
	return tmp;
}

void Collider::Push(Vector2f dif, Vector2f intersect, Collider* other)
{
	if (*solid && *other->solid)
	{
		if (intersect.x > intersect.y)
		{
			if (dif.x > 0.0f)
			{
				//Colliding left
				Move(intersect.x * (1.0f - *pushFactor), 0.0f);
				onColliding.Notify(other->gameObject->GetObjectTag(), "Left");
			}
			else
			{
				//Colliding right
				Move(-intersect.x * (1.0f - *pushFactor), 0.0f);
				onColliding.Notify(other->gameObject->GetObjectTag(), "Right");
			}
		}
		else
		{
			if (dif.y > 0.0f)
			{
				//Colliding top
				Move(0.0f, intersect.y * (1.0f - *pushFactor));
				onColliding.Notify(other->gameObject->GetObjectTag(), "Top");
			}
			else
			{
				//Colliding bottom
				Move(0.0f, -intersect.y * (1.0f - *pushFactor));
				onColliding.Notify(other->gameObject->GetObjectTag(), "Bottom");
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
	//We attach every component of the gameObject this Collider belongs to, to the list of listeners in onColliding and onNoLongerColliding.
	unordered_map<ComponentTag, Component*>::iterator it;
	for (it = (*gameObject->GetComponents()).begin(); it != (*gameObject->GetComponents()).end(); it++)
	{
		onColliding.Attach(it->second);
		onNoLongerColliding.Attach(it->second);
	}

	//We attach the GameWorld::Instance to onColliderDestroyed, so we can tell the GameWorld when this collider is about to be destroyed and should be
	//removed from the vectors of colliders and movable colliders in gameworld.
	onColliderDestroyed.Attach(GameWorld::GetInstance());
}

void Collider::Update(Time* timePerFrame)
{
	UpdateListOfCurrentCollisions();

	(*wall)[0].position.x = gameObject->GetPosition().x - size->x / 1.8f;
	(*wall)[0].position.y = gameObject->GetPosition().y - size->y / 2;

	(*wall)[1].position.y = gameObject->GetPosition().y - size->y / 2;
	(*wall)[1].position.x = gameObject->GetPosition().x + size->x / 1.8f;
}

void Collider::Destroy()
{
	currentCollisions.clear();
	//This Notify must be called before ~Collider to ensure that anything we are colliding with gets notified
	// that we are about to be deleted, so they can respond to this in time. Same with the GameWorld instance that is also a listener subscriebd to this event.
	onColliderDestroyed.Notify("ColliderDestroyed", this);
	Collider::~Collider();
}

ComponentTag Collider::ToEnum()
{
	return ComponentTag::COLLIDER;
}


void Collider::OnNotify(std::string eventName, IListener* sender)
{
	//This ensures that a collider is removed from our list of currentCollisions before the collider is completely
	//deleted from the game along with the gameObject it belongs to.
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

//TODO: Do we use this?
void Collider::AttachToColliderDestroyedEvent(IListener* listener)
{
	onColliderDestroyed.Attach(listener);
}
