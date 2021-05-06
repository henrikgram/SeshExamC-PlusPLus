#pragma once
#include "ICollisionListener.h"
#include "../Components/Collider.h"

class ICollisionListener
{
	virtual void NotifyOfCollision(Collider otherCollider, Collider myCollider) = 0;
};
