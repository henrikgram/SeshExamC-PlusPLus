#include "Headers/Component.h"
#include "Headers/GameObject.h"

Component::Component()
{
	//TODO: Link component to gameobject
}

Component::~Component()
{
}

void Component::Awake()
{
}

void Component::Start()
{
}

void Component::Update()
{
}

void Component::Destroy()
{
}

ComponentTag Component::ToEnum()
{
	return ComponentTag();
}
