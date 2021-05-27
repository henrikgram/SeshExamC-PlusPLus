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
	/// TODO: SUMMARY
	/// </summary>
	/// <param name="listener"></param>
	void Attach(IListener* listener);
	/// <summary>
	/// TODO: SUMMARY
	/// </summary>
	/// <param name="listener"></param>
	void Detach(IListener* listener);
	/// <summary>
	/// TODO: SUMMARY
	/// </summary>
	/// <param name="eventTitle"></param>
	/// <param name="sender"></param>
	void Notify(string eventTitle, IListener* sender);

private:
	std::list<IListener*> listeners;
};

#endif