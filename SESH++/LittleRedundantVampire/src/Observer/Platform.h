#pragma once
#include <SFML/Graphics.hpp>
#include "ICollisionListener.h"
using namespace sf;

class Platform : public ICollisionListener
{
public:
	Platform(Texture* texture, Vector2f size, Vector2f position);
	~Platform();

	/// <summary>
/// Tegner platformens sprite.
/// </summary>
/// <param name="window">Det vindue som vi skal render sprite i.</param>
	void Draw(RenderWindow& window);

	//Collider GetCollider() { return Collider(body); }

	// Inherited via ICollisionListener
	void Notify(std::string eventName);
	void NotifyOfCollision(Collider otherCollider, Collider myCollider);

private:
	RectangleShape body;
};

