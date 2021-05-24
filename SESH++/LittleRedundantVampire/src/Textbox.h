#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "GameObject.h"


/// <summary>
/// For creating ingame textbox for the npc's.
/// </summary>
class Textbox
{
public:
	Textbox();
	~Textbox();

	//TODO: const
	static Textbox* GetInstance();

private:
	static Textbox* instance;
	// TODO: Should be instantiated with "new" in the cpp file instead.
	const Textbox* textbox = new Textbox();
};

#endif