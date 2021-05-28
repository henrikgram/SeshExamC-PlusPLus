#ifndef ICOMMAND_H
#define ICOMMAND_H


/// <summary>
/// Command: Interface for commands.
/// </summary>
class ICommand
{
public:
	// = 0 makes this method a pure virtual, meaning that no implementation of Execute is needed in ICommand.
	// Having a pure virtual method means this class header becomes an interface (abstract class).
	// A class that inherits from this one must implement the pure virtual method to avoid becoming an abstract class as well.
	virtual void Execute() = 0;
};

#endif