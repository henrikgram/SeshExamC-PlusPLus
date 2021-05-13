#pragma once
#include <unordered_map>
#include "ICommand.h"
#include "SFML/Graphics.hpp"
#include "MoveCommand.h"
#include "AttackCommand.h"
#include "../Components/Movement.h"
using namespace sf;

class PlayerInvoker
{
private:
	PlayerInvoker(Movement& movementReceiver, AttackSpawner& attackReciever);

public:
	~PlayerInvoker();

	PlayerInvoker(PlayerInvoker& other) = delete;

	void operator=(const PlayerInvoker&) = delete;

	static PlayerInvoker* GetInstance(Movement& movementReceiver, AttackSpawner& attackReceiver);

	void InvokeCommand();

private:
	static PlayerInvoker* instance;
	Movement& movementReceiver;
	AttackSpawner& attackReceiver;

	unordered_map<Keyboard::Key, ICommand*> keyBinds;
	unordered_map<Keyboard::Key, ICommand*>::iterator keyIt;

	unordered_map<Keyboard::Key, ICommand*> releaseKeyBinds;
	unordered_map<Keyboard::Key, ICommand*>::iterator releaseKeyIt;
};


