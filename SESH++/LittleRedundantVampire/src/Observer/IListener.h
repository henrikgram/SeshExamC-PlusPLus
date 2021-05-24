#ifndef ILISTENER_H
#define ILISTENER_H

#include <string>


/// <summary>
/// Observer: Interface for listeners to events.
/// </summary>
class IListener
{
public:
	//TODO: Fix when merging with signe and henriks componentcode
	virtual void OnNotify(std::string eventName, IListener* sender) = 0;
};

#endif