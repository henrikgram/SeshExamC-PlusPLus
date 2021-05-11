#pragma once
#include <string>

class IListener
{
public:
	//TODO: Fix when merging with signe and henriks componentcode
	virtual void OnNotify(std::string eventName, IListener* sender) = 0;
};

