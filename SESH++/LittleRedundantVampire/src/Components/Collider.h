#ifndef COLLIDER_H
#define COLLIDER_H

#include <SFML/Graphics.hpp>
#include "../Observer/CollisionEvent.h"
#include "../Observer/IGameEvent.h"
#include "../Component.h"

using namespace sf;


/// <summary>
/// Component: Allows the object to handle collision in various ways.
/// </summary>
class Collider : public Component
{
public:
	/// <summary>
	/// Collider Constructor
	/// </summary>
	/// <param name="size"> The size of the collisionBox i.e. the rectangle surrounding the object </param>
	/// <param name="position"> Used to set the position of the collisionBox </param>
	/// <param name="pushFactor"> A float number between 0.0f and 1.0, where the lower the number the "lighter" the object seems. 1.0 means the object cannot be pushed.</param>
	/// <param name="solid"> Refers to whether or not the collider belongs to a solid object. Some objects are not solid and can be passed through such as ghosts.</param>
	Collider(Vector2f size, Vector2f position, float pushFactor, bool solid);
	~Collider();

	//Move should perhaps not be in this class. Collider shouldn't be responsible for moving an object perhaps a Rigidbody class.
	//Currently used for moving objects being pushed.
	
	/// <summary>
	/// Moves the gameobject that the collider belongs to according to the a vector2f based on the parameters deltaX and deltaY. 
	/// Is normally called from the Push method to Move the gameobject by how much it is being "pushed".
	/// </summary>
	/// <param name="deltaX"></param>
	/// <param name="deltaY"></param>
	void Move(float deltaX, float deltaY);

	/// <summary>
	/// Checks if this collider intersects with a different collider.
	/// </summary>
	/// <param name="other"> The collider we want to see if we're intersecting with </param>
	/// <returns></returns>
	bool CheckCollision(Collider* other);
	Vector2f GetPosition() const;
	Vector2f GetHalfsize() const;

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
	//RectangleShape* collisionBox;
	Vector2f* size;
	float* pushFactor;
	bool* solid;
	CollisionEvent onColliding;
	IGameEvent onNoLongerColliding;
	IGameEvent onColliderDestroyed;

	std::list<Collider*> currentCollisions;
};

#endif