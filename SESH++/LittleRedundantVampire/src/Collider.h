#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Collider
{
public:
	Collider(RectangleShape& body);
	~Collider();

	void Move(float deltaX, float deltaY) { body.move(deltaX, deltaY); }

	bool CheckCollision(Collider& other, float pushFactor);
	Vector2f GetPosition() { return body.getPosition(); }
	Vector2f GetHalfsize() { return body.getSize() / 2.0f; }

private:
	RectangleShape& body;
};

