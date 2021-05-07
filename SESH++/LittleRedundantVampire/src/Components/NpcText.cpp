#include "..\Headers\Components\NpcText.h"


NpcText::NpcText(String message)
{
    text = new Text();
    text->setString(message);
}

NpcText::~NpcText()
{

}

//NpcText* NpcText::SetText(String message)
//{ 
//    npcText = new NpcText();
//    text->setString(message);
//
//    return nullptr;
//}

void NpcText::Awake()
{
    font->loadFromFile("Asset/PlayfairDisplay-VariableFont_wght.ttf");
}

void NpcText::Start()
{
    text->setFont(*font);
    text->setCharacterSize(24);
    text->setFillColor(sf::Color::Red);
    text->setStyle(Text::Bold | Text::Italic);
}

void NpcText::Update()
{
}

void NpcText::Destroy()
{
}

ComponentTag NpcText::ToEnum()
{
    return ComponentTag::NPC_TEXT;
}