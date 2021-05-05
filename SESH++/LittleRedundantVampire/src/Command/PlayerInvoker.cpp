#include "../Headers/Command/PlayerInvoker.h"

PlayerInvoker::PlayerInvoker(Player& receiver) : receiver(receiver)
{
	keyBinds.insert(make_pair(Keyboard::A, new MoveCommand(receiver, Vector2f(-1.0f,0.0f))));
	keyBinds.insert(make_pair(Keyboard::D, new MoveCommand(receiver, Vector2f(1.0f, 0.0f))));
	keyBinds.insert(make_pair(Keyboard::W, new MoveCommand(receiver, Vector2f(0.0f, -1.0f))));
	keyBinds.insert(make_pair(Keyboard::S, new MoveCommand(receiver, Vector2f(0.0f, 1.0f))));
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

PlayerInvoker* PlayerInvoker::GetInstance(Player& receiver)
{
	if (instance == nullptr)
	{
		instance = new PlayerInvoker(receiver);
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
