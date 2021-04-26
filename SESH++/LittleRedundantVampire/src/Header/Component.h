#pragma once
#include "GameObject.h"
#include "Enum/Tag.h"

using namespace sf;
using namespace std;

class Component
{
public:
	//GameObject gameObject;
	// If true, use methods. If false, put on pause.
	bool isEnabled;

	Component();
	~Component();

	void Awake();
	void Start();
	void Update();
	void Destroy();
	Tag ToEnum();
};

