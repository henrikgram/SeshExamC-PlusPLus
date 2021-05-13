#pragma once
#include "../Component.h"
#include "SpriteRenderer.h"
#include "../GameWorld.h"
#include "TextMessage.h"

using namespace sf;

class Npc : public Component
{
private:
	GameObject* textBox = new GameObject();
	SpriteRenderer* textBoxSr = new SpriteRenderer();
	string* npcMessage = new string;
	int offset = 30;
	bool* textShown = new bool;

	void Awake() override;
	void Start() override;
	void Update(Time* timePerFrame) override;
	void Destroy() override;
	ComponentTag ToEnum() override;

	void OnNotifyCollision(ObjectTag otherTag, string side) override;

public:
	Npc(string* message);
	~Npc();

	void TextBoxPopup();
	void TextBoxRemoval();
};

