#include "TextMessage.h"

TextMessage::TextMessage(string* msg, Vector2f position)
{
	// TODO: Dunno if it's good that awake and start is run here, but I feel like it makes
	// sense since this object is never instantiated through the LevelManager? And why have
	// awake and start if we never use them?
	// Either way, I think it's much nicer to have code in awake and start to avoid
	// filling up TextMessage's constructor with a bunch of code.
	// Man, what a long-ass comment, huh.
	Awake();
	Start();

	text->setString(*msg);
	text->setPosition(position.x + offset, position.y + offset);
}

TextMessage::~TextMessage()
{

}

Text TextMessage::GetMessage()
{
	return *text;
}

void TextMessage::Awake()
{
	font = new Font();
	font->loadFromFile("Asset/PlayfairDisplay-VariableFont_wght.ttf");
}

void TextMessage::Start()
{
	text = new Text();
	text->setFont(*font);
	text->setCharacterSize(32);
	text->setFillColor(sf::Color::White);
	text->setStyle(Text::Bold | Text::Italic);
	text->setPosition(Vector2f(GameWorld::GetInstance()->GetScreenWidth() - (text->getGlobalBounds().width / 2), GameWorld::GetInstance()->GetScreenHeight() + (text->getGlobalBounds().height * 2)));
}

void TextMessage::Update(Time* timePerFrame)
{
	text->setPosition(Vector2f(GameWorld::GetInstance()->GetScreenWidth() - (text->getGlobalBounds().width / 2), GameWorld::GetInstance()->GetScreenHeight() + (text->getGlobalBounds().height *2)));
}

void TextMessage::Destroy()
{

}

ComponentTag TextMessage::ToEnum()
{
	return ComponentTag::TEXT_MESSAGE;
}