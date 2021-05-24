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
	AttackCommand(AttackSpawner& attackReceiver);
	~AttackCommand();

	// Inherited via ICommand
	void Execute();

private:
	AttackSpawner& attackReceiver;
};

#endif