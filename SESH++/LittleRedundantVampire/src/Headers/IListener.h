#pragma once
#include <string>

class IListener
{
public:
	//TODO: Fix when merging with signe and henriks componentcode
	virtual void Notify(std::string eventName/*, Component component*/) = 0;
};
