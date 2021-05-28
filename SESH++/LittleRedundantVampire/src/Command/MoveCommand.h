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

	/// <summary>
	/// The constructor for the MoveCommand
	/// </summary>
	/// <param name="movementReceiver"> Receiver refers to the object/class that holds the method we want to call in this case a Movement component</param>
	/// <param name="velocity"> velocity refers to how we want to move the object along the x and y axes.</param>
	MoveCommand(Movement& movementReceiver, Vector2f velocity);
	~MoveCommand();

	// Inherited via ICommand
	void Execute();

private:
	Movement& movementReceiver;
	Vector2f velocity;
};

#endif
