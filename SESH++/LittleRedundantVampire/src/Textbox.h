#pragma once
#include "GameObject.h"

class Textbox
{
public:
	Textbox();
	~Textbox();

	static Textbox* GetInstance();
	GameObject* DrawTextbox();

private:
	static Textbox* instance;
	const Textbox* textbox = new Textbox();
};