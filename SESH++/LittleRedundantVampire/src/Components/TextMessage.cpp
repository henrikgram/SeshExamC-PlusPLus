#include "TextMessage.h"

TextMessage::TextMessage(string* msg, Vector2f position)
{
	text = new Text();
	text->setString(*msg);
	text->setPosition(position.x + offset, position.y + offset);
	drawComponent = true;

	font = new Font();
	font->loadFromFile("Asset/PlayfairDisplay-VariableFont_wght.ttf");

	text->setFont(*font);
	text->setCharacterSize(32);
	text->setFillColor(sf::Color::White);
	text->setStyle(Text::Bold | Text::Italic);
	text->setPosition(Vector2f(GameWorld::GetInstance()->GetScreenWidth() - (text->getGlobalBounds().width / 2), 
							   GameWorld::GetInstance()->GetScreenHeight() + (text->getGlobalBounds().height * 2)));
}

TextMessage::~TextMessage()
{
}

void TextMessage::Awake()
{

}

void TextMessage::Start()
{
	
}

void TextMessage::Update(Time* timePerFrame)
{
	text->setPosition(Vector2f(GameWorld::GetInstance()->GetScreenWidth() - (text->getGlobalBounds().width / 2), GameWorld::GetInstance()->GetScreenHeight() + (text->getGlobalBounds().height *2)));
}

Text TextMessage::GetTextMessage()
{
	return *text;
}

void TextMessage::Destroy()
{
		TextMessage::~TextMessage();
}

ComponentTag TextMessage::ToEnum()
{
	return ComponentTag::TEXT_MESSAGE;
}
