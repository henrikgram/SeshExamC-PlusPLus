#pragma once
#include <unordered_map>
#include "ICommand.h"

class PlayerInputHandler
{
public:
	PlayerInputHandler();
	~PlayerInputHandler();

	void InvokeCommand();

private:
	unordered_map<Keyboard::Key, ICommand*> keyBinds;
	unordered_map<Keyboard::Key, ICommand*>::iterator keyIt;
};

