#include "Npc.h"


Npc::Npc(string* message)
{
	npcMessage = message;
	*textShown = false;
}

Npc::~Npc()
{

}

void Npc::TextBoxPopup(Vector2f boxPosition)
{
	if (!*textShown)
	{
		*textBox->objectTag = ObjectTag::TEXT_BOX;
		textBoxSr->SetSprite(TextureTag::TEXT_BOX);
		textBox->AddComponent(textBoxSr);
		textBox->position = new Vector2f(boxPosition);
		textBox->AddComponent(new TextMessage(npcMessage, boxPosition));
		(*GameWorld::GetInstance()->GetGameObjects()).push_back(textBox);
		*textShown = true;
	}
}

void Npc::TextBoxRemoval()
{
	if (*textShown)
	{
		textBoxSr->Destroy();
		textBox->Destroy();
		*textShown = true;
	}
}

void Npc::Awake()
{

}

void Npc::Start()
{

}

void Npc::Update(Time* timePerFrame)
{

}

void Npc::Destroy()
{
	Npc::~Npc();
}

ComponentTag Npc::ToEnum()
{
	return ComponentTag::NPC;
}

void Npc::NotifyCollision(ObjectTag otherTag)
{
	switch (otherTag)
	{
	case ObjectTag::PLAYER:
		TextBoxPopup(Vector2f(this->gameObject->position->x, this->gameObject->position->y - offset));
		//cout << "Hit";
		break;

	default:
		break;
	}
}