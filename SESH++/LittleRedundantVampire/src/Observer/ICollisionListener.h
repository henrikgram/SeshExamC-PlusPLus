#ifndef ICOLLISIONLISTENER_H
#define ICOLLISIONLISTENER_H

#include "../Enum/ObjectTag.h"
#include <string>

/// <summary>
/// Observer: Interface for collision listeners.
/// </summary>
class ICollisionListener
{
public:
	/// <summary>
	/// Executes code that should happen when Notify is called for an CollisionEvent that this listener is subscribed to. I.e. runs the code that should happen
	/// When we collide with another object.
	/// </summary>
	/// <param name="otherTag"> The ObjectTag of the other GameObject we are colliding with </param>
	/// <param name="side"> The side of the other GameObject that we are colliding with </param>
	virtual void OnNotifyCollision(ObjectTag otherTag, std::string side) = 0;
};

#endif