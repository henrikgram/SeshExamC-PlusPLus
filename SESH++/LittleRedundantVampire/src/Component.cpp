#include "Component.h"
#include "GameObject.h"
#include <iostream>

Component::~Component()
{
}

void Component::OnNotify(std::string eventName, IListener* sender)
{
}

void Component::OnNotifyCollision(ObjectTag otherTag, string side)
{
}