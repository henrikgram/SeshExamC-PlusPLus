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
#include "../Enum/ComponentTag.h"

using namespace sf;
using namespace std;

class GameObject 
{
public:
	//Map for all components attached to the gameobject
	unordered_map<ComponentTag, Component*> components;
	Transform* transform = new Transform();

	GameObject();
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
	/// Attaching a component to the gameobject
	/// </summary>
	/// <param name="component">Component to be attached</param>
	void AddComponent(Component * component);

	/// <summary>
	/// Gets a component based on ComponentTag.
	/// </summary>
	Component * GetComponent(ComponentTag tag);

	/// <summary>
	///  Calls Destroy for all components attached to the gameobject
	/// </summary>
	void Destroy();

private:
	unordered_map<ComponentTag, Component*>::iterator it;
};

#endif 

