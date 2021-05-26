#ifndef PLAYERINVOKER_H
#define PLAYERINVOKER_H

#include <unordered_map>
#include "ICommand.h"
#include "MoveCommand.h"
#include "AttackCommand.h"
#include "../Components/Movement.h"
#include "../Components/AttackSpawner.h"

using namespace sf;


/// <summary>
/// Command: Manages keybinds and executes the correct commands when a key is pressed.
/// </summary>
class PlayerInvoker
{
public:

	/// <summary>
	/// Give a reference to the AttackSpawner and Movement component from the Player object.
	/// </summary>
	/// <param name="movementReceiver"></param>
	/// <param name="attackReciever"></param>
	PlayerInvoker(Movement& movementReceiver, AttackSpawner& attackReciever);
	~PlayerInvoker();

	/// <summary>
	/// Check for pressed keys and execute the command for the key.
	/// </summary>
	void InvokeCommand();

private:

	Movement& movementReceiver;
	AttackSpawner& attackReceiver;

	unordered_map<Keyboard::Key, ICommand*> keyBinds;
	unordered_map<Keyboard::Key, ICommand*>::iterator keyIt;
};

#endif