#include "Headers\Global.h"


Global::Global()
{
	gameObjects = new vector<GameObject*>;
}

Global::~Global()
{
	delete instance;
	instance = nullptr;

	delete gameObjects;
	gameObjects = nullptr;
}

Global* Global::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Global();
	}

	return instance;
}

vector<GameObject*>* Global::GetGameObjects()
{
	return gameObjects;
}


// Sets the instance to  nullptr. Because static variables need a definition.
// Part of what makes the class a singleton.
Global* Global::instance = nullptr;
