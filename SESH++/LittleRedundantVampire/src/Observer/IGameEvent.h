#pragma once
#include <string>
#include <list>
#include "IListener.h"

using namespace std;

class IGameEvent
{
public:
	IGameEvent();
	~IGameEvent();

	void Attach(IListener* listener);
	void Detach(IListener* listener);
	void Notify(string eventTitle);

private:
	list<IListener*> listeners;
};