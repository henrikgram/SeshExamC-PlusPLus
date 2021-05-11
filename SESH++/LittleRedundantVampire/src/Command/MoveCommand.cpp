#include "MoveCommand.h"

MoveCommand::MoveCommand(Player& receiver, Vector2f velocity, string recieverDirection) : receiver(receiver)
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
