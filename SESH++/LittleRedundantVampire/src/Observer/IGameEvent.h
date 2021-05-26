#ifndef IGAMEEVENT_H
#define IGAMEEVENT_H

#include <string>
#include <list>
#include "IListener.h"

using namespace std;


//TODO: Remove I since it's no longer an interface.
/// <summary>
/// Observer: Game events.
/// </summary>
class IGameEvent
{
public:
	IGameEvent();
	~IGameEvent();

	void Attach(IListener* listener);
	void Detach(IListener* listener);
	void Notify(string eventTitle, IListener* sender);

private:
	std::list<IListener*> listeners;
};

#endif