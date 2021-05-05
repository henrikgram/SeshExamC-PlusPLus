#include "../Headers/Components/NPC.h"


GameObject NPC::TextBoxPopup()
{
	GameObject* go = new GameObject();
	SpriteRenderer* sr = new SpriteRenderer();
	sr->SetSprite(TextureTag::TEXTBOX);
	go->position = new Vector2<float>(200, 1);
	go->AddComponent(sr);
	return *go;
}

void NPC::TextBoxRemoval()
{
	sr->Destroy();
	go->Destroy();
}
