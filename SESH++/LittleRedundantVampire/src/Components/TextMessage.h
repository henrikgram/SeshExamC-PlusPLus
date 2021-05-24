#ifndef TEXTMESSAGE_H
#define TEXTMESSAGE_H

#include <string>
#include "../Component.h"
#include "../GameWorld.h"

using namespace std;


/// <summary>
/// Component: A text message that comes with a text and font.
/// Currently only used for NPC's.
/// </summary>
class TextMessage : public Component
{
private:
	Text* text;
	Font* font;
	int offset = 8;

	// Inherited via Component
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update(Time* timePerFrame) override;
	virtual void Destroy() override;
	virtual ComponentTag ToEnum() override;

public:
	TextMessage(string* msg, Vector2f position);
	~TextMessage();

	/// <summary>
	/// Returns the text.
	/// </summary>
	Text GetMessage();
};

#endif