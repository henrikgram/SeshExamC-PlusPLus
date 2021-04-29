#include "Headers/Component.h"
#include "Headers/GameObject.h"


Component::~Component()
{
	//TODO: check if destructor is called automatically, through subclasses destructor
	delete gameObject;
	gameObject = nullptr;
}