#include "Component.h"
#include "GameObject.h"
#include <iostream>


Component::~Component()
{
	//TODO: check if destructor is called automatically, through subclasses destructor
	delete gameObject;
	gameObject = nullptr;
}

void Component::OnNotify(std::string eventName, IListener* sender)
{
}

void Component::OnNotifyCollision(ObjectTag otherTag)
{
}
