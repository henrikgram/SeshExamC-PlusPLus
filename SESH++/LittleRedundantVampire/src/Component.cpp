#include "Component.h"
#include "GameObject.h"


Component::~Component()
{
	//TODO: check if destructor is called automatically, through subclasses destructor
	delete gameObject;
	gameObject = nullptr;
}

void Component::Notify(std::string eventName)
{
}
