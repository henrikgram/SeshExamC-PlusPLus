#pragma once
#include "ICommand.h"
#include "../Components/Player.h"

class MoveCommand : public ICommand
{
public:
	MoveCommand(Player& receiver, Vector2f* velocity);
	~MoveCommand();

	// Inherited via ICommand
	void Execute();

private:
	Player& receiver;
	Vector2f* velocity;
};