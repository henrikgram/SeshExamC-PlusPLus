#ifndef ATTACKCOMMAND_H
#define ATTACKCOMMAND_H

#include "ICommand.h"
#include "../Components/AttackSpawner.h"


/// <summary>
/// Command: The command that lets the player attack.
/// </summary>
class AttackCommand : public ICommand
{
public:
	/// <summary>
	/// Constructor for the attack command.
	/// </summary>
	/// <param name="attackReceiver">Reference to an attackspawner component.</param>
	AttackCommand(AttackSpawner& attackReceiver);
	~AttackCommand();

	// Inherited via ICommand
	void Execute();

private:
	AttackSpawner& attackReceiver;
};

#endif