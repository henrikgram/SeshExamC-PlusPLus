#include "MoveCommand.h"

MoveCommand::MoveCommand(Player& receiver, Vector2f* velocity) : receiver(receiver)
{
	this->velocity = velocity;
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
