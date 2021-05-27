#include "AttackCommand.h"


//Give AttackCommand a reference to the AttackSpawner component from the Player object.
AttackCommand::AttackCommand(AttackSpawner& attackReceiver) : attackReceiver(attackReceiver)
{
	//TODO: forst�r ikke helt hvad der sker her
}

AttackCommand::~AttackCommand()
{
}

void AttackCommand::Execute()
{
	//Creates a player attack when the player executes the attack command
	attackReceiver.CreateAttack(TextureTag::PLAYER_ATTACK_SHEET, ObjectTag::PLAYERATTACK);
}