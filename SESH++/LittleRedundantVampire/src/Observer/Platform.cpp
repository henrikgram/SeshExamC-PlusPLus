#include "Platform.h"

Platform::Platform(/*Texture* texture, Vector2f size, Vector2f position*/)
{
	something = new string("Hello");
	/*body.setTexture(texture);
	body.setOrigin(size / 2.0f);
	body.setSize(size);
	body.setPosition(position);*/
}

Platform::~Platform()
{
	delete something;
	something = nullptr;
}

//void Platform::Draw(RenderWindow& window)
//{
//	window.draw(body);
//}

void Platform::Awake()
{
}

void Platform::Start()
{
}

void Platform::Update(Time* timePerFrame)
{
	/*if (Keyboard::isKeyPressed(Keyboard::Delete));
	{
		this->gameObject->Destroy();
	}*/
}

void Platform::Destroy()
{
}

ComponentTag Platform::ToEnum()
{
	return ComponentTag::CRATE;
}
