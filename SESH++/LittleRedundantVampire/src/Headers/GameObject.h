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
	unordered_map<ComponentTag, Component*> components;

	GameObject(Texture* texture);
	GameObject();
	~GameObject();

	void Update(Time* timePerFrame);
	void Awake();
	void Start();
	void AddComponent(Component * component);
	Component * GetComponent(ComponentTag tag);
	//template <typename T> T GetComponent2(ComponentTag tag);
	void Destroy();

	//Sprite GetSprite();

private:
	//Sprite* sprite;
};

#endif 

//template<typename T>
//inline T GameObject::GetComponent2(ComponentTag tag)
//{
//	return components[tag];
//}