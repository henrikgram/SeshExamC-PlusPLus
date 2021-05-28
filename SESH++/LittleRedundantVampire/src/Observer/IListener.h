#ifndef ILISTENER_H
#define ILISTENER_H

#include <string>


/// <summary>
/// Observer: Interface for listeners to events.
/// </summary>
class IListener
{
public:
	/// <summary>
	/// Executes code that should happen when Notify is called for an event that this listener is subscribed to.
	/// </summary>
	/// <param name="eventName"> The name of the event that has occured </param>
	/// <param name="sender"> A listener, typically the one who called the Notify method. </param>
	virtual void OnNotify(std::string eventName, IListener* sender) = 0;
};

#endif