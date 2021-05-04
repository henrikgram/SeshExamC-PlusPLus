#include "Headers/GameObject.h"
#include "Headers/Component.h"

using namespace sf;
using namespace std;

GameObject::GameObject()
{

}

GameObject::GameObject(Vector2<float> position)
{
	this->position->x = position.x;
	this->position->y = position.y;
}

GameObject::~GameObject()
{

}

void GameObject::Update(Time* timePerFrame)
{
	it = components.begin();

	//iterates through the gameObjects and calls Update
	for (it = components.begin(); it != components.end(); it++)
	{
		it->second->Update();
	}
}

void GameObject::Awake()
{
	it = components.begin();

	//iterates through the gameObjects and calls Awake
	for (it = components.begin(); it != components.end(); it++)
	{
		it->second->Awake();
	}
}

void GameObject::Start()
{
	it = components.begin();

	//iterates through the gameObjects and calls Start
	for (it = components.begin(); it != components.end(); it++)
	{
		it->second->Start();
	}
}

void GameObject::AddComponent(Component* component)
{
	//adds the current gameobject as a parrent to the component
	component->gameObject = this;

	components.insert(make_pair(component->ToEnum(), component));
}

Component* GameObject::GetComponent(ComponentTag tag)
{
	return components[tag];
}

void GameObject::Destroy()
{
	it = components.begin();

	//iterates through the gameObjects and calls Destroy
	for (it = components.begin(); it != components.end(); it++)
	{
		it->second->Destroy();

		delete it->second;
		it->second = nullptr;
	}
}