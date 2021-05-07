#pragma once
#include "../Component.h"

using namespace sf;


class NpcText : public Component
{
private:
	Text* text;
	Font* font;
	NpcText* npcText;
	//NpcText* SetText(String message);

public:
	NpcText(String message);
	~NpcText();

	// Inherited via Component
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void Destroy() override;
	virtual ComponentTag ToEnum() override;
};

