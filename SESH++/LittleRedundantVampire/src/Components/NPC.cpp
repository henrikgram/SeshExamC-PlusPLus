#include "../Headers/Components/NPC.h"


NPC::NPC(String* message)
{
	message = new String();
}

NPC::~NPC()
{

}

GameObject NPC::TextBoxPopup(Vector2f boxPosition, String message)
{
	NpcText* text = new NpcText(message);
	GameObject* go = new GameObject();
	SpriteRenderer* sr = new SpriteRenderer();
	sr->SetSprite(TextureTag::TEXTBOX);
	go->position = new Vector2f(boxPosition);
	go->AddComponent(sr);
	go->AddComponent(text);
	return *go;
}

void NPC::TextBoxRemoval()
{
	sr->Destroy();
	go->Destroy();
}

void NPC::Awake()
{

}

void NPC::Start()
{

}

void NPC::Update()
{

}

void NPC::Destroy()
{
	NPC::~NPC();
}

ComponentTag NPC::ToEnum()
{
	return ComponentTag::NPC;
}

