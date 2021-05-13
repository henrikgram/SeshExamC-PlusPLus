#include "Npc.h"


Npc::Npc(string* message)
{
	npcMessage = message;
	*textShown = false;
}

Npc::~Npc()
{

}

void Npc::TextBoxPopup()
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
		// TODO: Remove from gameObjects Vector.
		//textBoxSr->Destroy();
		//textBox->Destroy();
		//*textShown = true;
	}
}

void Npc::Awake()
{
	*textBox->GetObjectTag() = ObjectTag::TEXT_BOX;
	//textBoxSr->SetSprite(TextureTag::TEXT_BOX);
	*textBox->GetPosition() = Vector2f(GameWorld::GetInstance()->GetScreenWidth(), GameWorld::GetInstance()->GetScreenHeight() + (textBoxSr->GetSprite().getLocalBounds().height / 2));
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
		*textBox->GetPosition() = Vector2f(GameWorld::GetInstance()->GetScreenWidth(), GameWorld::GetInstance()->GetScreenHeight() + (textBoxSr->GetSprite().getLocalBounds().height / 2));
		
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

void Npc::OnNotifyCollision(ObjectTag otherTag, string side)
{
	switch (otherTag)
	{
	case ObjectTag::PLAYER:
		TextBoxPopup();
		//cout << "Hit";
		break;

	default:
		break;
	}
}