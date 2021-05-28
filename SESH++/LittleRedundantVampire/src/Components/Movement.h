#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "../Component.h"


class Movement : public Component
{
public:
	/// <summary>
	/// Constructor for movement component.
	/// </summary>
	/// <param name="speed">The movement speed.</param>
	/// <param name="velocity">The direction.</param>
	Movement(float speed, Vector2f velocity);
	~Movement();

	// Inherited via Component
	void Awake() override;
	void Start() override;
	void Update(Time* timePerFrame) override;
	void Destroy() override;
	ComponentTag ToEnum() override;


	//own methods

	/// <summary>
	/// Lets the object move.
	/// </summary>
	/// <param name="velocity"></param>
	void Move(Vector2f velocity);

private:
	/// <summary>
	/// Makes it so the object doesn't move faster diagonally.
	/// </summary>
	void Normalize();

private:
	float speed;
	Vector2f* velocity;
};

#endif