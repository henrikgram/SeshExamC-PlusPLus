#pragma once
#include "ICommand.h"
#include "../Components/Player.h"


class AttackCommand : public ICommand
{
public:
	AttackCommand(AttackSpawner& attackReceiver);
	~AttackCommand();

	// Inherited via ICommand
	void Execute();

private:
	AttackSpawner& attackReceiver;
};