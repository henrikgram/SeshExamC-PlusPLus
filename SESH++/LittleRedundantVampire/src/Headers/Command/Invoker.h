#pragma once
#include <unordered_map>
#include "ICommand.h"
#include "SFML/Graphics.hpp"
#include "MoveCommand.h"
using namespace sf;

class Invoker
{
private:
	Invoker(Player& receiver);

public:
	~Invoker();

	Invoker(Invoker& other) = delete;

	void operator=(const Invoker&) = delete;

	static Invoker* GetInstance(Player& receiver);

	void InvokeCommand();

private:
	static Invoker* instance;
	Player& receiver;

	unordered_map<Keyboard::Key, ICommand*> keyBinds;
	unordered_map<Keyboard::Key, ICommand*>::iterator keyIt;
};


