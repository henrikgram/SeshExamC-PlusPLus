#include "Platform.h"

Platform::Platform(Texture* texture, Vector2f size, Vector2f position)
{
	body.setTexture(texture);
	body.setOrigin(size / 2.0f);
	body.setSize(size);
	body.setPosition(position);
}

Platform::~Platform()
{
}

void Platform::Draw(RenderWindow& window)
{
	window.draw(body);
}

void Platform::Notify(std::string eventName)
{
}

void Platform::NotifyOfCollision(Collider otherCollider, Collider myCollider)
{
}

