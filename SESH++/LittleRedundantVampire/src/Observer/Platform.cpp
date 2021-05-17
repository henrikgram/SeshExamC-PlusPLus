#include "Platform.h"

Platform::Platform(/*Texture* texture, Vector2f size, Vector2f position*/)
{
	timer = new float(0.0f);
	//something = new string("Hello");
	/*body.setTexture(texture);
	body.setOrigin(size / 2.0f);
	body.setSize(size);
	body.setPosition(position);*/
}

Platform::~Platform()
{
	//delete something;
	//something = nullptr;
	delete timer;
	timer = nullptr;
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

	if (*timer >= 100)
	{
		this->gameObject->CallSelfDestruct();
		return;
	}
	else
	{
		cout << *timer;
		(*timer) += 1;
	}
}

void Platform::Destroy()
{
	Platform::~Platform();
}

ComponentTag Platform::ToEnum()
{
	return ComponentTag::CRATE;
}
