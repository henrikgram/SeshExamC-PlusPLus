#include "CollisionEvent.h"
#include <string>


CollisionEvent::CollisionEvent()
{
}

CollisionEvent::~CollisionEvent()
{
    listeners.clear();
}

void CollisionEvent::Attach(ICollisionListener* listener)
{
    listeners.push_back(listener);
}

void CollisionEvent::Detach(ICollisionListener* listener)
{
    listeners.remove(listener);
}

void CollisionEvent::Notify(ObjectTag otherTag, std::string side)
{
    std::list<ICollisionListener*>::iterator iterator = listeners.begin();
    while (iterator != listeners.end()) {
        (*iterator)->OnNotifyCollision(otherTag, side);
        ++iterator;
    }
}