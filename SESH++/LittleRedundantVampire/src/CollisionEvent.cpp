#include "CollisionEvent.h"
#include "IGameEvent.h"

CollisionEvent::CollisionEvent()
{
    IGameEvent::SetEventTitle("Collision");
}

CollisionEvent::~CollisionEvent()
{
}

void CollisionEvent::Attach(IListener* listener)
{
	listeners.push_back(listener);
}

void CollisionEvent::Detach(IListener* listener)
{
	listeners.remove(listener);
}

void CollisionEvent::Notify()
{
    std::list<IListener*>::iterator iterator = listeners.begin();
    while (iterator != listeners.end()) {
        (*iterator)->Notify(IGameEvent::GetEventTitle());
        ++iterator;
    }
}
