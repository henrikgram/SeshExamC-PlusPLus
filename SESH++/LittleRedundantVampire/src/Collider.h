#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Collider
{
public:
	Collider(RectangleShape& body);
	~Collider();

	void Move(float deltaX, float deltaY) const { body.move(deltaX, deltaY); }

	bool CheckCollision(const Collider& other, float pushFactor);
	Vector2f GetPosition() const { return body.getPosition(); }
	Vector2f GetHalfsize() const { return body.getSize() / 2.0f; }

private:
	RectangleShape& body;
};

