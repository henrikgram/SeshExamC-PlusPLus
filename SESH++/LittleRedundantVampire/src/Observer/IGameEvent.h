#pragma once
#include <string>
#include <list>
#include "IListener.h"

using namespace std;

//TODO: Remove I since it's no longer an interface.
class IGameEvent
{
public:
	IGameEvent(string eventTitle);
	~IGameEvent();

	void Attach(IListener* listener);
	void Detach(IListener* listener);
	void Notify();

	string GetEventTitle() const { return *eventTitle; }

private:
	string* eventTitle;
	std::list<IListener*> listeners;
};

