#pragma once
#include <list>
#include "IGameEvent.h"

class CollisionEvent : public IGameEvent
{
public:
	CollisionEvent();
	~CollisionEvent();

	void Attach(IListener* listener);
	void Detach(IListener* listener);
	void Notify();

private:
	std::list<IListener*> listeners;
};

