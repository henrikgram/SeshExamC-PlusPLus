#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"
using namespace sf;

class Platform
{
public:
	Platform(Texture* texture, Vector2f size, Vector2f position);
	~Platform();

	/// <summary>
/// Tegner platformens sprite.
/// </summary>
/// <param name="window">Det vindue som vi skal render sprite i.</param>
	void Draw(RenderWindow& window);

	Collider GetCollider() { return Collider(body); }

private:
	RectangleShape body;
};

