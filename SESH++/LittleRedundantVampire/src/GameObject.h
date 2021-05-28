#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class Component;
//Forward declaration, to make sure the compiler knows that it exist.
//Two classes can't include from each other, because that would create an infinite loop

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

#include "Enum/ComponentTag.h"
#include "Enum/ObjectTag.h"
#include "Observer/IGameEvent.h"
#include "Observer/IListener.h"

using namespace sf;
using namespace std;

//TODO:* Maybe we can use the same rectangle for collider, sr and ac.


/// <summary>
/// The objects in the game. You can add components to them.
/// </summary>
class GameObject : public IListener
{
public:
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
	Component* GetComponent(ComponentTag tag) const;

	//TODO:* It doesn't make sense to have a constant Get for a pointer. Might as well just make a public const pointer instead and skip the Get.
	//It's also completely pointless to have a Get that returns the pointers, which allows you to change the value but not the address,
	//and then a Set for just returning the value.
	//Either do a Get that only returns the value and a Set that only alters the value,
	//or just make a constant public pointer.
	//This is true for many cases where we have a Get-method for returning a pointer.
	Vector2f GetPosition() const;
	void SetPosition(Vector2f newPosition);

	//See these following Get and Set for examples of how we should have done it with Position also.

	ObjectTag GetObjectTag() const;
	void SetObjectTag(ObjectTag newObjectTag);

	char GetDirection() const;
	void SetDirection(char newDirection);

	bool GetIsMovable() const;
	/// <summary>
	/// Sets isMovable. Determines whether the object can move or not.
	/// Used for making the Player stand still while attack is active.
	/// </summary>
	/// <param name="newValue">'T' for True. 'F' for False.</param>
	void SetIsMovable(char newValue);

	unordered_map<ComponentTag, Component*>* GetComponents() const;

	bool GetShouldDraw() const;
	/// <summary>
	/// Sets shouldDraw. Determines whether the object should be dawn or not.
	/// Used for making the Player's healthbar only visible when taking damage.
	/// </summary>
	/// <param name="newValue">'T' for True. 'F' for False.</param>
	void SetShouldDraw(char newValue);

	/// <summary>
	/// Method that notifies listeners of the GameEvent 'onCallSelfDestruct' (like GameWorld) that this GameObject is ready to be deleted.
	/// Can be called from the components belonging to the gameobject.
	/// </summary>
	void CallSelfDestruct();

	///// <summary>
	///// Used to attach a listener (like Gameworld) to the event onCallSelfDestruct.
	///// </summary>
	///// <param name="listener"></param>
	//void AddListenerToCallSelfDestruct(IListener* listener);

private:
	Vector2f* position;
	ObjectTag* objectTag;
	char* direction;
	bool* shouldDraw;
	IGameEvent onCallSelfdestruct;
	bool* isMovable;
	//Map for all components attached to the gameobject
	unordered_map<ComponentTag, Component*>* components;

	// Inherited via IListener
	virtual void OnNotify(std::string eventName, IListener* sender) override;
};

#endif