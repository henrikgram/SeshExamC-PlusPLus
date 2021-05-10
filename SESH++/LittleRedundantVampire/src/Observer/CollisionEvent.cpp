#include "CollisionEvent.h"

CollisionEvent::CollisionEvent()
{
}

CollisionEvent::~CollisionEvent()
{
    /*for (auto&& listener : listeners) {
        delete listener;
    }*/
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

void CollisionEvent::Notify(ObjectTag otherTag)
{
    std::list<ICollisionListener*>::iterator iterator = listeners.begin();
    while (iterator != listeners.end()) {
        (*iterator)->NotifyCollision(otherTag);
        ++iterator;
    }
}
