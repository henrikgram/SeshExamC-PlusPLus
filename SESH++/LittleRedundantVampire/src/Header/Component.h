#pragma once
#include "GameObject.h"

using namespace sf;
using namespace std;

class Component
{
public:
	GameObject * gameObject;
	// If true, use methods. If false, put on pause.
	bool isEnabled;

	//Component();
	//~Component();

	virtual void Awake() = 0;
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Destroy() = 0;
	virtual Tag ToEnum();
};

