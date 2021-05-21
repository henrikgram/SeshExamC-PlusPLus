#ifndef PLAYERINVOKER_H
#define PLAYERINVOKER_H

#include <unordered_map>
#include "ICommand.h"
#include "MoveCommand.h"
#include "AttackCommand.h"
#include "../Components/Movement.h"
#include "../Components/AttackSpawner.h"

using namespace sf;


class PlayerInvoker
{
private:
	/// <summary>
	/// Give a reference to the AttackSpawner and Movement component from the Player object.
	/// </summary>
	/// <param name="movementReceiver"></param>
	/// <param name="attackReciever"></param>
	PlayerInvoker(Movement& movementReceiver, AttackSpawner& attackReciever);

public:
	~PlayerInvoker();

	PlayerInvoker(PlayerInvoker& other) = delete; //TODO: Explain in detail. Part of singleton

	void operator=(const PlayerInvoker&) = delete; //Part of singleton

	/// <summary>
	/// Gets the singleton instance.
	/// </summary>
	/// <param name="movementReceiver"></param>
	/// <param name="attackReceiver"></param>
	/// <returns></returns>
	static PlayerInvoker* GetInstance(Movement& movementReceiver, AttackSpawner& attackReceiver); //Part of singleton

	/// <summary>
	/// Check for pressed keys and execute the command for the key.
	/// </summary>
	void InvokeCommand();

private:
	static PlayerInvoker* instance;

	Movement& movementReceiver;
	AttackSpawner& attackReceiver;

	unordered_map<Keyboard::Key, ICommand*> keyBinds;
	unordered_map<Keyboard::Key, ICommand*>::iterator keyIt;
};

#endif