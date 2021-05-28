#include "GameEvent.h"

GameEvent::GameEvent()
{
}

GameEvent::~GameEvent()
{
}

void GameEvent::Attach(IListener* listener)
{
	listeners.push_back(listener);
}

void GameEvent::Detach(IListener* listener)
{
	listeners.remove(listener);
}

void GameEvent::Notify(string eventTitle, IListener* sender)
{
	std::list<IListener*>::iterator iterator = listeners.begin();
	while (iterator != listeners.end()) {
		(*iterator)->OnNotify(eventTitle, sender);
		++iterator;
	}
}