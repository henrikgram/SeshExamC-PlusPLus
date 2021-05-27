#ifndef COLLIDER_H
#define COLLIDER_H

#include <SFML/Graphics.hpp>
#include "../Observer/CollisionEvent.h"
#include "../Observer/IGameEvent.h"
#include "../Component.h"

using namespace sf;

//TODO: Colliders are fucked again.

/// <summary>
/// Component: Allows the object to handle collision in various ways.
/// </summary>
class Collider : public Component
{
public:
	/// <summary>
	/// TODO: SUMMARY
	/// </summary>
	/// <param name="size"></param>
	/// <param name="position"></param>
	/// <param name="pushFactor"></param>
	/// <param name="solid"></param>
	Collider(Vector2f size, Vector2f position, float pushFactor, bool solid);
	~Collider();

	//Move should perhaps not be in this class. Collider shouldn't be responsible for moving an object perhaps a Rigidbody class.
	//Currently used for moving objects being pushed.
	
	/// <summary>
	/// TODO: SUMMARY
	/// </summary>
	/// <param name="deltaX"></param>
	/// <param name="deltaY"></param>
	void Move(float deltaX, float deltaY);

	/// <summary>
	/// TODO: SUMMARY
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	bool CheckCollision(Collider* other);
	Vector2f GetPosition() const { return *gameObject->GetPosition(); }
	Vector2f GetHalfsize() const { return collisionBox->getSize() / 2.0f; }

	/// <summary>
	/// TODO: SUMMARY
	/// </summary>
	/// <param name="delta"></param>
	/// <param name="intersect"></param>
	/// <param name="other"></param>
	void Push(Vector2f delta, Vector2f intersect, Collider* other);

	/// <summary>
	/// TODO: SUMMARY
	/// </summary>
	void UpdateListOfCurrentCollisions();

	// Inherited via Component
	void Awake() override;
	void Start() override;
	void Update(Time* timePerFrame) override;
	void Destroy() override;
	ComponentTag ToEnum() override;

	void OnNotify(std::string eventName, IListener* sender) override;
	void AttachToColliderDestroyedEvent(IListener* listener);

	VertexArray* wall;

private:
	RectangleShape* collisionBox;
	float* pushFactor;
	bool* solid;
	CollisionEvent onColliding;
	IGameEvent onNoLongerColliding;
	IGameEvent onColliderDestroyed;

	std::list<Collider*> currentCollisions;
};

#endif