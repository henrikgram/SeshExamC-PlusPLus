#include "AttackCommand.h"
#include "../Components/AttackSpawner.h"


AttackCommand::AttackCommand(AttackSpawner& attackReceiver) : attackReceiver(attackReceiver)
{
}

AttackCommand::~AttackCommand()
{
}

void AttackCommand::Execute()
{
	attackReceiver.CreateAttack("left");
}



