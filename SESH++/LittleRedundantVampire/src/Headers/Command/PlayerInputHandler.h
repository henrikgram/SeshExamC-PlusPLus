#pragma once

#include <unordered_map>
#include "ICommand.h"
#include "MoveCommand.h"

class PlayerInputHandler
{
private:
	PlayerInputHandler(Player& receiver);

public:
	~PlayerInputHandler();

	PlayerInputHandler(PlayerInputHandler& other) = delete;

	void operator=(const PlayerInputHandler&) = delete;

	static PlayerInputHandler* GetInstance(Player& receiver);

	void InvokeCommand();

private:
	static PlayerInputHandler* instance;
	Player& receiver;

	unordered_map<Keyboard::Key, ICommand*> keyBinds;
	unordered_map<Keyboard::Key, ICommand*>::iterator keyIt;
};

PlayerInputHandler* PlayerInputHandler::instance = nullptr;;


