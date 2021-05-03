#include "../Headers/Command/PlayerInputHandler.h"

PlayerInputHandler::PlayerInputHandler()
{

}

PlayerInputHandler::~PlayerInputHandler()
{
	keyIt = keyBinds.begin();

	//Calls delete on every Command* stored in the map, to de-allocate the memory, before clearing the map. 
	for (keyIt = keyBinds.begin(); keyIt != keyBinds.end(); keyIt++)
	{
		delete keyIt->second;
	}
	keyBinds.clear();
}

void PlayerInputHandler::InvokeCommand()
{
	keyIt = keyBinds.begin();

	for (keyIt = keyBinds.begin(); keyIt != keyBinds.end(); keyIt++)
	{
		keyIt->second->Execute();
	}
}
