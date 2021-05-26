#ifndef ILISTENER_H
#define ILISTENER_H

#include <string>


/// <summary>
/// Observer: Interface for listeners to events.
/// </summary>
class IListener
{
public:
	virtual void OnNotify(std::string eventName, IListener* sender) = 0;
};

#endif