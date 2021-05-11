#pragma once
#include "../Enum/ObjectTag.h"

class ICollisionListener
{
public:
	//TODO: Fix when merging with signe and henriks componentcode
	virtual void OnNotifyCollision(ObjectTag otherTag) = 0;
};
