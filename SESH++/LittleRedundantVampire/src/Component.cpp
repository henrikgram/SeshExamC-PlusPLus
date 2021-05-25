#include "Component.h"
#include "GameObject.h"
#include <iostream>

Component::~Component()
{
}

void Component::OnNotify(std::string eventName, IListener* sender)
{
	if (eventName == "NoLongerCollidingWith")
	{
		// TODO: SIGNE: uuuh, nani the fuck?
	}
}

void Component::OnNotifyCollision(ObjectTag otherTag, string side)
{
}