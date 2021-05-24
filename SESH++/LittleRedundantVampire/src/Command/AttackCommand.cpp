#include "AttackCommand.h"


//Give AttackCommand a reference to the AttackSpawner component from the Player object.
AttackCommand::AttackCommand(AttackSpawner& attackReceiver) : attackReceiver(attackReceiver)
{
}

AttackCommand::~AttackCommand()
{
}

void AttackCommand::Execute()
{
// TODO: Comment sounds a bit weird but I might just be too tired to get it.
	//PlayerAttack because only the commands are only used by the player. 
	attackReceiver.CreateAttack(TextureTag::PLAYER_ATTACK_SHEET, ObjectTag::PLAYERATTACK);
}