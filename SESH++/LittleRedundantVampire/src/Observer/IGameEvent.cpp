#include "IGameEvent.h"

IGameEvent::IGameEvent(string eventTitle)
{
	this->eventTitle = new string(eventTitle);
}

IGameEvent::~IGameEvent()
{
	delete eventTitle;
	eventTitle = nullptr;


}

void IGameEvent::Attach(IListener* listener)
{
	listeners.push_back(listener);
}

void IGameEvent::Detach(IListener* listener)
{
	listeners.remove(listener);
}

void IGameEvent::Notify()
{
	std::list<IListener*>::iterator iterator = listeners.begin();
	while (iterator != listeners.end()) {
		(*iterator)->Notify(*eventTitle);
		++iterator;
	}
}