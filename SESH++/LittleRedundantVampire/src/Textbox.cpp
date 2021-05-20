#include "Textbox.h"

Textbox::Textbox()
{
}

Textbox::~Textbox()
{
}

Textbox* Textbox::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Textbox();
	}

	return instance;
}

GameObject* Textbox::DrawTextbox()
{
	return nullptr;
}



// Sets the instance to  nullptr. Because static variables need a definition.
// Part of what makes the class a singleton.
Textbox* Textbox::instance = nullptr;