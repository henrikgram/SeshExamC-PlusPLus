#pragma once
#include <SFML/Graphics.hpp>
#include "CollisionEvent.h"
#include "IListener.h"

using namespace sf;

class Collider : protected IListener
{
public:
	Collider(RectangleShape& body);
	~Collider();

	void Move(float deltaX, float deltaY) const { body.move(deltaX, deltaY); }

	bool CheckCollision(const Collider& other, float pushFactor);
	Vector2f GetPosition() const { return body.getPosition(); }
	Vector2f GetHalfsize() const { return body.getSize() / 2.0f; }
	void Notify(std::string eventName/*, Component component*/);

private:
	RectangleShape& body;
	CollisionEvent onColliding;
};

