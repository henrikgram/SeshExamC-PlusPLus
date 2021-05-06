#pragma once
#include <SFML/Graphics.hpp>
#include "../Observer/CollisionEvent.h"
#include "../Component.h"

using namespace sf;

class Collider : public Component, protected ICollisionListener
{
public:
	Collider(Vector2f size, Vector2f position, float pushFactor, bool solid);
	~Collider();

	//TODO: Move should perhaps not be in this class. Collider shouldn't be responsible for moving an object.
	//void Move(float deltaX, float deltaY) const { collisionBox->move(deltaX, deltaY); }

	bool CheckCollision(Collider* other);
	Vector2f GetPosition() const { return *gameObject->position; }
	Vector2f GetHalfsize() const { return collisionBox->getSize() / 2.0f; }

	// Inherited via Component
	void Awake() override;
	void Start() override;
	void Update(Time* timePerFrame) override;
	void Destroy() override;
	ComponentTag ToEnum() override;

private:
	RectangleShape* collisionBox;
	float* pushFactor;
	bool* solid;
	CollisionEvent onColliding;
};

