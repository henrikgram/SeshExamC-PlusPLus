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
		//TODO: Tjek om vi bare kan kalde delete inde fra components (suicide)
	}

	components->clear();
}

void GameObject::AddComponent(Component* component)
{
	//adds the current gameobject as a parrent to the component
	component->gameObject = this;

	components->insert(make_pair(component->ToEnum(), component));
}

Component* GameObject::GetComponent(ComponentTag tag)
{
	return (*components)[tag];
}

void GameObject::SetPosition(Vector2f newPosition)
{
	*position = newPosition;
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