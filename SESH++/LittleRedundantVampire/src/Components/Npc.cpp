#include "Npc.h"


Npc::Npc(string* message)
{
	npcMessage = message;
	*textShown = false;
}

Npc::~Npc()
{

}

void Npc::TextBoxPopup(/*Vector2f boxPosition*/)
{
	if (!*textShown)
	{
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
	*textBox->objectTag = ObjectTag::TEXT_BOX;
	textBoxSr->SetSprite(TextureTag::TEXT_BOX);
	*textBox->position = Vector2f(GameWorld::GetInstance()->GetScreenWidth() - (textBoxSr->GetSprite().getLocalBounds().width / 2), GameWorld::GetInstance()->GetScreenHeight());
	//textBoxSr->GetSprite().setOrigin(textBoxSr->GetSprite().getLocalBounds().width / 2, textBoxSr->GetSprite().getLocalBounds().height / 2);
	textBox->AddComponent(textBoxSr);
	textBox->AddComponent(new TextMessage(npcMessage, Vector2f(GameWorld::GetInstance()->GetScreenWidth() - (textBoxSr->GetSprite().getLocalBounds().width / 2), GameWorld::GetInstance()->GetScreenHeight())));
}

void Npc::Start()
{

}

void Npc::Update(Time* timePerFrame)
{
	if (*textShown)
	{
		textBox->position = new Vector2f(GameWorld::GetInstance()->GetScreenWidth() - (textBoxSr->GetSprite().getLocalBounds().width /2), GameWorld::GetInstance()->GetScreenHeight());
		
	}
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
		TextBoxPopup(/*Vector2f(this->gameObject->position->x, this->gameObject->position->y - offset)*/);
		//cout << "Hit";
		break;

	default:
		break;
	}
}