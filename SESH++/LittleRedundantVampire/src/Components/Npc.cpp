#include "Npc.h"


Npc::Npc(string message)
{
	textBox = new GameObject();
	textShown = new bool(false);
	npcMessage = new string(message);
	textBoxSr = new SpriteRenderer(TextureTag::TEXT_BOX);
}

Npc::~Npc()
{
	delete npcMessage;
	npcMessage = nullptr;

	delete npcMessage;
	npcMessage = nullptr;
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
	// If the text is supposed to be shown, which means the text is currently vissible,
	// we remove the textbox from the list of gameObjects, then make textShown false afterwards,
	// so the text disappears as well.
	if (*textShown)
	{
		// Goes through the list of gameObjects.
		for (auto i = (*GameWorld::GetInstance()->GetGameObjects()).begin(); i != (*GameWorld::GetInstance()->GetGameObjects()).end();)
		{
			// If we found the textbox, remove it.
			if (*(*i)->GetObjectTag() == ObjectTag::TEXT_BOX)
			{
				i = (*GameWorld::GetInstance()->GetGameObjects()).erase(i);
			}
			else
			{
				++i;
			}
		}
		// Makes sure the text is no longer drawn.
		*textShown = false;
	}
}

void Npc::Awake()
{
	*textBox->GetObjectTag() = ObjectTag::TEXT_BOX;
	*textBox->GetPosition() = Vector2f(GameWorld::GetInstance()->GetScreenWidth(), GameWorld::GetInstance()->GetScreenHeight() + (textBoxSr->GetSprite().getLocalBounds().height / 2));
	textBox->AddComponent(textBoxSr);
	textBox->AddComponent(new TextMessage(npcMessage, Vector2f(GameWorld::GetInstance()->GetScreenWidth() - (textBoxSr->GetSprite().getLocalBounds().width / 2), GameWorld::GetInstance()->GetScreenHeight())));
}

void Npc::Start()
{
}

void Npc::Update(Time* timePerFrame)
{
	// Only draws the text if textShown is true.
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
		break;

	default:
		break;
	}
}

void Npc::OnNotify(std::string eventName, IListener* sender)
{
	if (eventName == "NoLongerCollidingWith")
	{
		// Remove the textbox when no longer colliding with player.
		TextBoxRemoval();
	}
}
