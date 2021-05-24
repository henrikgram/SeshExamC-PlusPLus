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
	//TODO: Fix when merging with signe and henriks componentcode
	virtual void OnNotifyCollision(ObjectTag otherTag, std::string side) = 0;
};

#endif