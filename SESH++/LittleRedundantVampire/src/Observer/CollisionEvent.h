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
	/// TODO: SUMMARY
	/// </summary>
	/// <param name="listener"></param>
	void Attach(ICollisionListener* listener);
	/// <summary>
	/// TODO: SUMMARY
	/// </summary>
	/// <param name="listener"></param>
	void Detach(ICollisionListener* listener);
	/// <summary>
	/// TODO: SUMMARY
	/// </summary>
	/// <param name="otherTag"></param>
	/// <param name="side"></param>
	void Notify(ObjectTag otherTag, std::string side);

private:
	std::list<ICollisionListener*> listeners;
};

#endif