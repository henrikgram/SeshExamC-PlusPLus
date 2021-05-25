#include "MoveCommand.h"


//Give MoveCommand a reference to the Movement component from the Player object.
MoveCommand::MoveCommand(Movement& movementReceiver, Vector2f velocity) : movementReceiver(movementReceiver)
{
	//TODO: Behøvede vi virkelig at lave vector new, eller er det bare monogame flashbacks?
	this->velocity = new Vector2f(velocity);
}

MoveCommand::~MoveCommand()
{
	delete velocity;
	velocity = nullptr;
}

void MoveCommand::Execute()
{
	//if the Player can move, run the Move method.
	if (*movementReceiver.gameObject->GetIsMovable())
	{
		movementReceiver.Move(*velocity);
	}
}
