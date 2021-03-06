#include "PlayerInvoker.h"

PlayerInvoker::PlayerInvoker(Movement& movementReceiver, AttackSpawner& attackReceiver) :
	movementReceiver(movementReceiver),
	attackReceiver(attackReceiver)
{
	//Maps the keys with a command.
	keyBinds.insert(make_pair(Keyboard::A, new MoveCommand(movementReceiver, Vector2f(-1.0f, 0.0f))));
	keyBinds.insert(make_pair(Keyboard::D, new MoveCommand(movementReceiver, Vector2f(1.0f, 0.0f))));
	keyBinds.insert(make_pair(Keyboard::W, new MoveCommand(movementReceiver, Vector2f(0.0f, -1.0f))));
	keyBinds.insert(make_pair(Keyboard::S, new MoveCommand(movementReceiver, Vector2f(0.0f, 1.0f))));
	keyBinds.insert(make_pair(Keyboard::Space, new AttackCommand(attackReceiver)));
}

PlayerInvoker::~PlayerInvoker()
{
	keyIt = keyBinds.begin();

	//Calls delete on every Command* stored in the map, to de-allocate the memory, before clearing the map. 
	for (keyIt = keyBinds.begin(); keyIt != keyBinds.end(); keyIt++)
	{
		delete keyIt->second;
		keyIt->second = nullptr;
	}
	keyBinds.clear();
}

void PlayerInvoker::InvokeCommand()
{
	keyIt = keyBinds.begin();

	for (keyIt = keyBinds.begin(); keyIt != keyBinds.end(); keyIt++)
	{
		if (Keyboard::isKeyPressed((*keyIt).first))
		{
			keyIt->second->Execute();
		}
	}
}
