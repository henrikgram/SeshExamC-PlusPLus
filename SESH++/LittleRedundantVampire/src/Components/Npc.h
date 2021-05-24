#ifndef NPC_H
#define NPC_H

#include "../Component.h"
#include "SpriteRenderer.h"
#include "../GameWorld.h"
#include "TextMessage.h"

using namespace sf;


/// <summary>
/// Component: Character that player can interact with. Ghosts.
/// </summary>
class Npc : public Component
{
public:
	Npc(string* message);
	~Npc();

	/// <summary>
	/// Makes sure the textbox is drawn in the game.
	/// </summary>
	void TextBoxPopup();
	/// <summary>
	/// Removes the textbox from the game and makes textShown false, so that the text disappears as well.
	/// </summary>
	void TextBoxRemoval();

	// Inherited via Component
	void Awake() override;
	void Start() override;
	void Update(Time* timePerFrame) override;
	void Destroy() override;
	ComponentTag ToEnum() override;

	void OnNotifyCollision(ObjectTag otherTag, string side) override;
	void OnNotify(std::string eventName, IListener* sender) override;


private:
	//TODO: We have to stop declaring pointers as new in the header files because it appears that it gives us problems down the line with meory management.
	//TODO: Change these so new keyword is called somewhere else in the cpp file. Prefereably the constructor. 

	GameObject* textBox;
	SpriteRenderer* textBoxSr;
	// The text used for the NPC textbox.
	string* npcMessage;
	// Determines whether or not the text and texbox should be drawn.
	bool* textShown;
};

#endif