#pragma once
#include "../Component.h"
#include "SpriteRenderer.h"
#include "../GameWorld.h"
#include "TextMessage.h"

using namespace sf;

class Npc : public Component
{
private:
	//TODO: We have to stop declaring pointers as new in the header files because it appears that it gives us problems down the line with meory management.
	//Change these so new keyword is called somewhere else in the cpp file. Prefereably the constructor. 
	GameObject* textBox = new GameObject();
	SpriteRenderer* textBoxSr = new SpriteRenderer(TextureTag::TEXT_BOX);
	string* npcMessage = new string;

	int offset = 30;
	bool* textShown = new bool;

	void Awake() override;
	void Start() override;
	void Update(Time* timePerFrame) override;
	void Destroy() override;
	ComponentTag ToEnum() override;

	void OnNotifyCollision(ObjectTag otherTag, string side) override;

	void OnNotify(std::string eventName, IListener* sender) override;

public:
	Npc(string* message);
	~Npc();

	void TextBoxPopup();
	void TextBoxRemoval();
};

