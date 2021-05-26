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
	virtual void OnNotifyCollision(ObjectTag otherTag, std::string side) = 0;
};

#endif