#include "PlayerInvoker.h"
#include "../Components/AttackSpawner.h"

PlayerInvoker::PlayerInvoker(Player& receiver, AttackSpawner& attackReceiver) : 
	receiver(receiver), 
	attackReceiver(attackReceiver)
{
	keyBinds.insert(make_pair(Keyboard::A, new MoveCommand(receiver, Vector2f(-1.0f,0.0f), *receiver.gameObject->direction = "left")));
	keyBinds.insert(make_pair(Keyboard::D, new MoveCommand(receiver, Vector2f(1.0f, 0.0f), *receiver.gameObject->direction = "right")));
	keyBinds.insert(make_pair(Keyboard::W, new MoveCommand(receiver, Vector2f(0.0f, -1.0f), *receiver.gameObject->direction = "up")));
	keyBinds.insert(make_pair(Keyboard::S, new MoveCommand(receiver, Vector2f(0.0f, 1.0f), *receiver.gameObject->direction = "down")));
	keyBinds.insert(make_pair(Keyboard::Space, new AttackCommand(attackReceiver)));
}

PlayerInvoker::~PlayerInvoker()
{
	keyIt = keyBinds.begin();

	//Calls delete on every Command* stored in the map, to de-allocate the memory, before clearing the map. 
	for (keyIt = keyBinds.begin(); keyIt != keyBinds.end(); keyIt++)
	{
		delete keyIt->second;
	}
	keyBinds.clear();
}

PlayerInvoker* PlayerInvoker::GetInstance(Player& receiver, AttackSpawner& attackReceiver)
{
	if (instance == nullptr)
	{
		instance = new PlayerInvoker(receiver, attackReceiver);
	}

	return instance;
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

PlayerInvoker* PlayerInvoker::instance = nullptr;;
