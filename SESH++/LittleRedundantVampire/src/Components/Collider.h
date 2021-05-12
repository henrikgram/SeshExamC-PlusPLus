#pragma once
#include <SFML/Graphics.hpp>
#include "../Observer/CollisionEvent.h"
#include "../Observer/IGameEvent.h"
#include "../Component.h"

using namespace sf;

class Collider : public Component
{
public:
	Collider(Vector2f size, Vector2f position, float pushFactor, bool solid);
	~Collider();

	//TODO: Move should perhaps not be in this class. Collider shouldn't be responsible for moving an object perhaps a Rigidbody class.
	void Move(float deltaX, float deltaY);

	//TODO: Should maybe be a void method
	bool CheckCollision(Collider* other);
	Vector2f GetPosition() const { return *gameObject->position; }
	Vector2f GetHalfsize() const { return collisionBox->getSize() / 2.0f; }

	void Push(Vector2f delta, Vector2f intersect, Collider* other);
	void UpdateListOfCurrentCollisions();

	// Inherited via Component
	void Awake() override;
	void Start() override;
	void Update(Time* timePerFrame) override;
	void Destroy() override;
	ComponentTag ToEnum() override;

	void OnNotify(std::string eventName, IListener* sender) override;

private:
	RectangleShape* collisionBox;
	float* pushFactor;
	bool* solid;
	CollisionEvent onColliding;
	IGameEvent onNoLongerColliding;
	IGameEvent onOtherGameObjDestroyed;

	std::list<Collider*> currentCollisions;
};

