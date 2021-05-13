#include "MoveCommand.h"

MoveCommand::MoveCommand(Movement& movementReceiver, Vector2f velocity) : receiver(receiver)
{
	this->velocity = new Vector2f(velocity);
}

MoveCommand::~MoveCommand()
{
	delete velocity;
	velocity = nullptr;
}

void MoveCommand::Execute()
{
	receiver.Move(*velocity);
}
