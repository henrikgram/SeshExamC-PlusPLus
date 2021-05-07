#pragma once
#include "../GameObject.h"
#include "../Components/SpriteRenderer.h"
#include "../Headers/Components/NpcText.h"

class NPC : public Component
{
private:
	GameObject* go;
	SpriteRenderer* sr;
	String* textMessage;

	NPC(String* message);
	~NPC();

	void Awake() override;
	void Start() override;
	void Update() override;
	void Destroy() override;
	ComponentTag ToEnum() override;

public:
	GameObject TextBoxPopup(Vector2f boxPosition, String message);
	void TextBoxRemoval();
};