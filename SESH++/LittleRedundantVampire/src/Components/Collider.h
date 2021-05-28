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
	/// <param name="size"> The size of the collider (x = width and y = height) </param>
	/// <param name="position"> Used to set the position of the collider </param>
	/// <param name="pushFactor"> A float number between 0.0f and 1.0, where the lower the number the "lighter" the object seems. 1.0 means the object cannot be pushed.</param>
	/// <param name="solid"> Refers to whether or not the collider belongs to a solid object. Some objects are not solid and can be passed through such as ghosts.</param>
	Collider(Vector2f size, Vector2f position, float pushFactor, bool solid);
	~Collider();

	//TODO:* Move should perhaps not be in this class. Collider shouldn't be responsible for moving an object perhaps a Rigidbody class.
	//Currently used for moving objects being pushed.
	
	/// <summary>
	/// Moves the gameobject that the collider belongs to according to the a vector2f based on the parameters deltaX and deltaY. 
	/// Is normally called from the Push method to Move the gameobject by how much it is being "pushed".
	/// </summary>
	/// <param name="deltaX"></param>
	/// <param name="deltaY"></param>
	void Move(float difX, float difY);

	/// <summary>
	/// Checks if this collider intersects with a different collider.
	/// </summary>
	/// <param name="other"> The collider we want to see if we're intersecting with </param>
	/// <returns></returns>
	bool CheckCollision(Collider* other);

	Vector2f GetPosition() const;
	Vector2f GetHalfsize() const;

	/// <summary>
	/// Pushes solid objects when they intersect, based on their pushfactor.
	/// </summary>
	/// <param name="delta"></param>
	/// <param name="intersect"></param>
	/// <param name="other"></param>
	void Push(Vector2f dif, Vector2f intersect, Collider* other);

	/// <summary>
	/// Checks if we are still intersecting with the colliders on our list of currentCollisions. 
	/// If not the event onNoLongerColliding is called and the collider is removed from the list. The collider is also detached
	/// from the listeners of the event onColliderDestroyed because we are no longer interested in telling this other collider if we are destroyed. 
	/// </summary>
	void UpdateListOfCurrentCollisions();

	// Inherited via Component
	void Awake() override;
	void Start() override;
	void Update(Time* timePerFrame) override;
	void Destroy() override;
	ComponentTag ToEnum() override;

	void OnNotify(std::string eventName, IListener* sender) override;

	VertexArray* Wall;

private:
	Vector2f* size;
	float* pushFactor;
	bool* solid;
	CollisionEvent onColliding;
	IGameEvent onNoLongerColliding;
	IGameEvent onColliderDestroyed;

	std::list<Collider*> currentCollisions;
};

#endif