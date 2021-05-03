#pragma once
#include "../Components/Player.h"

class ICommand
{
public:
	virtual void Execute() = 0;
};
