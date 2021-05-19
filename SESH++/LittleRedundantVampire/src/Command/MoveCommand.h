#pragma once
#include "ICommand.h"
#include "../Components/Player.h"
#include "../Components/Movement.h"

class MoveCommand : public ICommand
{
public:
	MoveCommand(Movement& movementReceiver, Vector2f velocity);
	~MoveCommand();

	// Inherited via ICommand
	void Execute();

private:
	Movement& movementReceiver;
	Vector2f* velocity;
};