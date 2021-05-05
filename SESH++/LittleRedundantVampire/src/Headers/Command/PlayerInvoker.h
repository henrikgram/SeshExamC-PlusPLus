#pragma once
#include <unordered_map>
#include "ICommand.h"
#include "SFML/Graphics.hpp"
#include "MoveCommand.h"
using namespace sf;

class PlayerInvoker
{
private:
	PlayerInvoker(Player& receiver);

public:
	~PlayerInvoker();

	PlayerInvoker(PlayerInvoker& other) = delete;

	void operator=(const PlayerInvoker&) = delete;

	static PlayerInvoker* GetInstance(Player& receiver);

	void InvokeCommand();

private:
	static PlayerInvoker* instance;
	Player& receiver;

	unordered_map<Keyboard::Key, ICommand*> keyBinds;
	unordered_map<Keyboard::Key, ICommand*>::iterator keyIt;
};


