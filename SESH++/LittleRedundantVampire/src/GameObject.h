#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class Component;
//forward declaration, to make sure the compiles knows that it exist
//TWo classes cant include from each other, because that would create an infinite loop

/*
* FROM STACK OVERFLOW
* You cannot have two classes directly contain objects of the other type,
since otherwise you'd need infinite space for the object
(since foo has a bar that has a foo that has a bar that etc.)

You can indeed do this by having the two classes store pointers to one another, though.
To do this, you'll need to use forward declarations so that the two classes know of each other's existence:
https://stackoverflow.com/questions/4964482/how-to-create-two-classes-in-c-which-use-each-other-as-data
*/

#include <SFML/graphics.hpp>
#include <iostream>
#include <unordered_map>

//#include "Component.h"
#include "Enum/ComponentTag.h"
#include "Enum/ObjectTag.h"
#include "Observer/IGameEvent.h"
#include "Observer/IListener.h"

using namespace sf;
using namespace std;

class GameObject : public IListener
{
public:
	//Map for all components attached to the gameobject
	unordered_map<ComponentTag, Component*> components;

	GameObject();
	GameObject(Vector2<float> position);
	~GameObject();

	/// <summary>
	/// Calls Update for all components attached to the gameobject
	/// </summary>
	/// <param name="timePerFrame">Used for frame dependent update</param>
	void Update(Time* timePerFrame);

	/// <summary>
	/// Calls Awake for all components attached to the gameobject
	/// </summary>
	void Awake();

	/// <summary>
	/// Calls Start for all components attached to the gameobject
	/// </summary>
	void Start();

	/// <summary>
	///  Calls Destroy for all components attached to the gameobject
	/// </summary>
	void Destroy();


	/// <summary>
	/// Attaching a component to the gameobject
	/// </summary>
	/// <param name="component">Component to be attached</param>
	void AddComponent(Component* component);

	/// <summary>
	/// Gets a component based on ComponentTag.
	/// </summary>
	Component* GetComponent(ComponentTag tag);

	Vector2f* GetPosition() const { return position; }

	ObjectTag* GetObjectTag() const { return objectTag; }

	string* GetDirection() const { return direction; }

	bool* GetShouldDraw() const { return shouldDraw; }

	/// <summary>
	/// Method that notifies listeners of the GameEvent 'onCallSelfDestruct' (like GameWorld) That this GameObject is ready to be deleted. 
	/// Can be called from the components belonging to the gameobject.
	/// </summary>
	void CallSelfDestruct();

	/// <summary>
	/// Used to attach a listener (like Gameworld) to the event onCallSelfDestruct.
	/// </summary>
	/// <param name="listener"></param>
	void AddListenerToCallSelfDestruct(IListener* listener);

private:
	unordered_map<ComponentTag, Component*>::iterator it;

	Vector2f* position;

	ObjectTag* objectTag;

	string* direction;

	bool* shouldDraw;

	IGameEvent onCallSelfdestruct;

	// Inherited via IListener
	virtual void OnNotify(std::string eventName, IListener* sender) override;
};

#endif
