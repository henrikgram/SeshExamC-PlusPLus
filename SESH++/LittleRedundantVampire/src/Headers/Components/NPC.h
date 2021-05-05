#pragma once
#include "../GameObject.h"
#include "../Components/SpriteRenderer.h"

class NPC : public GameObject
{
private:
	GameObject* go;
	SpriteRenderer* sr;

public:
	GameObject TextBoxPopup();
	void TextBoxRemoval();
};