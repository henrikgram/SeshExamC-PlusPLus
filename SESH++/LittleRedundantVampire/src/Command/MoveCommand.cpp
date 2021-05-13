#include "MoveCommand.h"

MoveCommand::MoveCommand(Player& receiver, Vector2f velocity) : receiver(receiver)
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
	if (*velocity == Vector2f(-1.0f, 0.0f))
	{
		*receiver.gameObject->GetDirection() = "left";
	}
	else if (*velocity == Vector2f(1.0f, 0.0f))
	{
		*receiver.gameObject->GetDirection() = "right";
	}
	else if (*velocity == Vector2f(0.0f, -1.0f))
	{
		*receiver.gameObject->GetDirection() = "up";
	}
	else if (*velocity == Vector2f(0.0f, 1.0f))
	{
		*receiver.gameObject->GetDirection() = "down";
	}

	receiver.Move(*velocity);
}
