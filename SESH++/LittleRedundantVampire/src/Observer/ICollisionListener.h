#pragma once
#include "../Enum/ObjectTag.h"
#include <string>

class ICollisionListener
{
public:
	//TODO: Fix when merging with signe and henriks componentcode
	virtual void OnNotifyCollision(ObjectTag otherTag, std::string side) = 0;
};
