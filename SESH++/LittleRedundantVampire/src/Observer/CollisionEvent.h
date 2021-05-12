#pragma once
#include <list>
#include <string>
#include "ICollisionListener.h"
#include "../Enum/ObjectTag.h"

class CollisionEvent
{
public:
	CollisionEvent();
	~CollisionEvent();

	void Attach(ICollisionListener* listener);
	void Detach(ICollisionListener* listener);
	void Notify(ObjectTag otherTag, std::string side);

private:
	std::list<ICollisionListener*> listeners;
};

