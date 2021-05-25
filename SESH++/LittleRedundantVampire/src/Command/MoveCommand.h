#ifndef MOVECOMMAND_H
#define MOVECOMMAND_H

#include "ICommand.h"
#include "../Components/Movement.h"


/// <summary>
/// Command: The command that lets the player move.
/// </summary>
class MoveCommand : public ICommand
{
public:
	MoveCommand(Movement& movementReceiver, Vector2f velocity);
	~MoveCommand();

	// Inherited via ICommand
	void Execute();

private:
	Movement& movementReceiver;
	Vector2f velocity;
};

#endif