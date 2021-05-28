#ifndef COLLISIONEVENT_H
#define COLLISIONEVENT_H

#include <list>
#include <string>
#include "ICollisionListener.h"
#include "../Enum/ObjectTag.h"


/// <summary>
/// Observer: Manages collision events.
/// </summary>
class CollisionEvent
{
public:
	CollisionEvent();
	~CollisionEvent();
	/// <summary>
	/// Attaches a listener to the event. 
	/// </summary>
	/// <param name="listener"> the listener we want to attach </param>
	void Attach(ICollisionListener* listener);
	/// <summary>
	/// Detaches a listener from the event, if it is on the list of listeners. 
	/// </summary>
	/// <param name="listener"> the listener we want to detach </param>
	void Detach(ICollisionListener* listener);
	/// <summary>
	/// Calls the OnNotify method in every listener on the list of listeners. 
	/// Tells them an event has happened, in this case a collisionEvent, so tells the listeners they are colliding with a different object with a collider.
	/// </summary>
	/// <param name="otherTag">The ObjectTag of the object we are colliding with </param>
	/// <param name="side">The side of the object we are colliding with </param>
	void Notify(ObjectTag otherTag, std::string side);

private:
	std::list<ICollisionListener*> listeners;
};

#endif