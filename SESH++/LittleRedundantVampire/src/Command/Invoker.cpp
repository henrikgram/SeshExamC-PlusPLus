#include "../Headers/Command/Invoker.h"

Invoker::Invoker(Player& receiver) : receiver(receiver)
{
	keyBinds.insert(make_pair(Keyboard::A, new MoveCommand(receiver, new Vector2f(-1.0f,0.0f))));
	keyBinds.insert(make_pair(Keyboard::D, new MoveCommand(receiver, new Vector2f(1.0f, 0.0f))));
	keyBinds.insert(make_pair(Keyboard::W, new MoveCommand(receiver, new Vector2f(0.0f, -1.0f))));
	keyBinds.insert(make_pair(Keyboard::S, new MoveCommand(receiver, new Vector2f(0.0f, 1.0f))));
}

Invoker::~Invoker()
{
	keyIt = keyBinds.begin();

	//Calls delete on every Command* stored in the map, to de-allocate the memory, before clearing the map. 
	for (keyIt = keyBinds.begin(); keyIt != keyBinds.end(); keyIt++)
	{
		delete keyIt->second;
	}
	keyBinds.clear();
}

Invoker* Invoker::GetInstance(Player& receiver)
{
	if (instance == nullptr)
	{
		instance = new Invoker(receiver);
	}

	return instance;
}

void Invoker::InvokeCommand()
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

Invoker* Invoker::instance = nullptr;;
