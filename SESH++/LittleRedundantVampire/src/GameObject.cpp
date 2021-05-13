#include "GameObject.h"
#include "Component.h"

using namespace sf;
using namespace std;

GameObject::GameObject()
{
	shouldDraw = new bool;
	*shouldDraw = true;

	direction = new string;
	*direction = "left";

	position = new Vector2f;

	objectTag = new ObjectTag;
}

GameObject::GameObject(Vector2<float> position)
{
	shouldDraw = new bool;
	*shouldDraw = true;

	direction = new string;
	*direction = "left";

	this->position = new Vector2f;
	(*this->position).x = position.x;
	(*this->position).y = position.y;

	objectTag = new ObjectTag;
}

GameObject::~GameObject()
{
	delete shouldDraw;
	shouldDraw = nullptr;

	delete direction;
	direction = nullptr;

	delete position;
	position = nullptr;

	delete objectTag;
	objectTag = nullptr;
}

void GameObject::Update(Time* timePerFrame)
{
	it = components.begin();

	//iterates through the gameObjects and calls Update
	for (it = components.begin(); it != components.end(); it++)
	{
		if (it->second != nullptr)
		{
			it->second->Update(timePerFrame);
		}

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

Vector2f* GameObject::GetPosition()
{
	return position;
}

ObjectTag* GameObject::GetObjectTag()
{
	return objectTag;
}

string* GameObject::GetDirection()
{
	return direction;
}

bool* GameObject::GetShouldDraw()
{
	return shouldDraw;
}