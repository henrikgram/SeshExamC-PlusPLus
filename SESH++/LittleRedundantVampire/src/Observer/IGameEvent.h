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
	/// <summary>
	/// Attaches a listener to the event. 
	/// </summary>
	/// <param name="listener"> The listener we want to attach </param>
	void Attach(IListener* listener);
	/// <summary>
	/// Detaches a listener from the event, if it is on the list of listeners.
	/// </summary>
	/// <param name="listener"> The listener we want to detach </param>
	void Detach(IListener* listener);
	/// <summary>
	/// Calls the OnNotify method in every listener on the list of listeners. 
	/// Tells them a GameEvent has happened and provides the title of the event and the one sender who called Notify for the event. 
	/// </summary>
	/// <param name="eventTitle"> A string title that describes the type of event. </param>
	/// <param name="sender"> A listener. Typically the one that called Notify. </param>
	void Notify(string eventTitle, IListener* sender);

private:
	std::list<IListener*> listeners;
};

#endif