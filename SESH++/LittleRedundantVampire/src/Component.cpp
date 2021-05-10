#include "Component.h"
#include "GameObject.h"


Component::~Component()
{
	//TODO: check if destructor is called automatically, through subclasses destructor
	delete gameObject;
	gameObject = nullptr;
}

void Component::OnNotify(std::string eventName)
{
}

void Component::NotifyCollision(ObjectTag otherTag)
{
}
