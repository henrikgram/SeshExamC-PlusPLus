#include "GameObject.h"
#include "Component.h"
#include "GameWorld.h"

using namespace sf;
using namespace std;


GameObject::GameObject()
{
	shouldDraw = new bool;
	*shouldDraw = true;

	direction = new char;
	*direction = 'N';

	isMovable = new bool;
	*isMovable = false;

	position = new Vector2f;

	objectTag = new ObjectTag;

	components = new unordered_map<ComponentTag, Component*>;
}

GameObject::GameObject(Vector2<float> position)
{
	shouldDraw = new bool;
	*shouldDraw = true;

	direction = new char;
	*direction = 'N';

	isMovable = new bool;
	*isMovable = false;

	this->position = new Vector2f;
	(*this->position).x = position.x;
	(*this->position).y = position.y;

	objectTag = new ObjectTag;

	components = new unordered_map<ComponentTag, Component*>;
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

	delete components;
	components = nullptr;

	delete isMovable;
	isMovable = nullptr;
}

void GameObject::Update(Time* timePerFrame)
{
	unordered_map<ComponentTag, Component*>::iterator it = components->begin();

	//iterates through the gameObjects and calls Update
	for (it = components->begin(); it != components->end(); it++)
	{
		if (it->second != nullptr)
		{
			it->second->Update(timePerFrame);
		}
	}
}

void GameObject::Awake()
{
	unordered_map<ComponentTag, Component*>::iterator it = components->begin();

	//iterates through the gameObjects and calls Awake
	for (it = components->begin(); it != components->end(); it++)
	{
		it->second->Awake();
	}
}

void GameObject::Start()
{
	unordered_map<ComponentTag, Component*>::iterator it = components->begin();

	//iterates through the gameObjects and calls Start
	for (it = components->begin(); it != components->end(); it++)
	{
		it->second->Start();
	}

	//TODO:* Optimize this so only objects that need to be destroyed during runtime can do the following.
	// GameWorld::Instance is attached so that when an object calls the selfdestruct method,
	// GameWorld is notified that the object is ready to be deleted.
	onCallSelfdestruct.Attach(GameWorld::GetInstance());
}

void GameObject::Destroy()
{
	unordered_map<ComponentTag, Component*>::iterator it = components->begin();

	//iterates through the gameObjects and calls Destroy
	for (it = components->begin(); it != components->end(); it++)
	{
		it->second->Destroy();

		delete it->second;
		it->second = nullptr;
	}

	components->clear();
}

void GameObject::AddComponent(Component* component)
{
	//adds the current gameobject as a parrent to the component
	component->gameObject = this;

	components->insert(make_pair(component->ToEnum(), component));
}

Component* GameObject::GetComponent(ComponentTag tag) const
{
	return (*components)[tag];
}

Vector2f GameObject::GetPosition() const
{
	return *position;
}

void GameObject::SetPosition(Vector2f newPosition)
{
	*position = newPosition;
}

ObjectTag GameObject::GetObjectTag() const
{
	return *objectTag;
}

void GameObject::SetObjectTag(ObjectTag newObjectTag)
{
	*objectTag = newObjectTag;
}

char GameObject::GetDirection() const
{
	return *direction;
}

void GameObject::SetDirection(char newDirection)
{
	*direction = newDirection;
}

bool GameObject::GetIsMovable() const
{
	return *isMovable;
}

void GameObject::SetIsMovable(bool newValue)
{
	*isMovable = newValue;
}

unordered_map<ComponentTag, Component*>* GameObject::GetComponents() const
{
	return components;
}

bool GameObject::GetShouldDraw() const
{
	return *shouldDraw;
}

void GameObject::SetShouldDraw(bool newValue)
{
	*shouldDraw = newValue;
}

void GameObject::CallSelfDestruct()
{
	onCallSelfdestruct.Notify("DeleteObject", this);
	//GameWorld::GetInstance()->GetObjectsToBeDeleted()->push(this);
}

//void GameObject::AddListenerToCallSelfDestruct(IListener* listener)
//{
//	onCallSelfdestruct.Attach(listener);
//}

void GameObject::OnNotify(std::string eventName, IListener* sender)
{
}