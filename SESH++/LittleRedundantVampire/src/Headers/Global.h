#pragma once
#include "GameObject.h"
#include <iostream>

using namespace std;


class Global
{
public:
	/// <summary>
	/// Returns the instance of the Asset class
	/// </summary>
	static Global* GetInstance();

	vector<GameObject*>* GetGameObjects();


private:
	static Global* instance;
	vector<GameObject*>* gameObjects;

	Global();
	~Global();
};

