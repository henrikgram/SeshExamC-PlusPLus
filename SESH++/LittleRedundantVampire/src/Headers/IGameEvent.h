#pragma once
#include <string>
#include "IListener.h"

using namespace std;

class IGameEvent
{
public:
	virtual void Attach(IListener* listener) = 0;
	virtual void Detach(IListener* listener) = 0;
	virtual void Notify(/*Component* other*/) = 0;

	string GetEventTitle() const { return eventTitle; }
	void SetEventTitle(string newTitle) { eventTitle = newTitle; }

private:
	string eventTitle;
};

