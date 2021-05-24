#ifndef COLLISIONEVENT_H
#define COLLISIONEVENT_H

#include <list>
#include <string>
#include "ICollisionListener.h"
#include "../Enum/ObjectTag.h"


/// <summary>
/// Observer: Manages collision events.
/// </summary>
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

#endif