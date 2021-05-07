#pragma once
#include "../Enum/ObjectTag.h"

class ICollisionListener
{
public:
	//TODO: Fix when merging with signe and henriks componentcode
	virtual void NotifyCollision(ObjectTag otherTag) = 0;
};
