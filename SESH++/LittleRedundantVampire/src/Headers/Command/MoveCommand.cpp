#include "MoveCommand.h"

MoveCommand::MoveCommand(Player& receiver, Vector2f& velocity)
{
	this->receiver = receiver;
	this->velocity = velocity;
}

MoveCommand::~MoveCommand()
{
}

void MoveCommand::Execute()
{
	receiver.Move(velocity);
}
