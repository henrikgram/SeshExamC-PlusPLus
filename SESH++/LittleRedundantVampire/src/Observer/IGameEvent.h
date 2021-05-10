#pragma once
#include <string>
#include "IListener.h"

using namespace std;

class IGameEvent
{
public:
	void Attach(IListener* listener);
	void Detach(IListener* listener);
	void Notify();

	string GetEventTitle() const { return eventTitle; }
	void SetEventTitle(string newTitle) { eventTitle = newTitle; }

private:
	string eventTitle;
};

