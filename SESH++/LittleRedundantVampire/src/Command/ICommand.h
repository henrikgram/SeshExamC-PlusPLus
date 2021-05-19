#ifndef ICOMMAND_H
#define ICOMMAND_H

class ICommand
{
public:
	// = 0 makes this method a pure virtual, meaning that no implementation of Execute is needed in ICommand.
	// Having a pure virtual method means this class header becomes an interface (abstract class).
	virtual void Execute() = 0;
};

#endif