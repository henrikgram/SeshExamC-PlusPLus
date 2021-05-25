#ifndef COMPONENT_H
#define COMPONENT_H

#include "GameObject.h"
#include "Enum/ComponentTag.h"
#include "Observer/IListener.h"
#include "Observer/ICollisionListener.h"
#include <string>

using namespace std;


/// <summary>
/// Virtual component to define component classes.
/// </summary>
class Component : public IListener, public ICollisionListener
{
public:
	//TODO: make this an interface
	GameObject* gameObject;

	~Component();

	/// <summary>
	/// Setup code that is the first thing to run once an object has been instantiated.
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
	/// Gets a component's tag.
	/// </summary>
	/// <returns></returns>
	virtual ComponentTag ToEnum() = 0;

	// Inherited via IListener
	virtual void OnNotify(std::string eventName, IListener* sender) override;

	// Inherited via ICollisionListener
	virtual void OnNotifyCollision(ObjectTag otherTag, std::string side) override;
	bool drawComponent = false;
};

#endif