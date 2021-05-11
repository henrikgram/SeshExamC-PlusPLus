#pragma once

#include "GameObject.h"
#include "Enum/ComponentTag.h"
#include "Observer/IListener.h"
#include "Observer/ICollisionListener.h"


using namespace std;

class Component : protected IListener, protected ICollisionListener
{
public:
	GameObject* gameObject;

	// If true, use methods. If false, put on pause.
	bool isEnabled;

	~Component();

	//TODO: Add more info on awake and start once we know what we run in them.

	/// <summary>
	/// Runs first once an object has been instantiated.
	/// </summary>
	virtual void Awake() = 0;

	/// <summary>
	/// Runs after awake.To run Setup code that is dependent on other code (run in awake)
	/// </summary>
	virtual void Start() = 0;

	/// <summary>
	/// Runs all update code needed to update specific objects.
	/// For example if an object moves.
	/// </summary>
	virtual void Update(Time* timePerFrame) = 0;

	/// <summary>
	/// Destroy and remove the component from the game.
	/// </summary>
	virtual void Destroy() = 0;

	/// <summary>
	/// Gets a components tag.
	/// </summary>
	/// <returns></returns>
	virtual ComponentTag ToEnum() = 0;

	// Inherited via IListener
	virtual void OnNotify(std::string eventName, IListener* sender) override;

	// Inherited via ICollisionListener
	virtual void OnNotifyCollision(ObjectTag otherTag) override;
};

