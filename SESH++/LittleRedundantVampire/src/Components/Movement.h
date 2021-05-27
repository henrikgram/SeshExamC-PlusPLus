#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "../Component.h"


class Movement : public Component
{
public:
	/// <summary>
	/// TODO: SUMMARY
	/// </summary>
	/// <param name="speed"></param>
	/// <param name="velocity"></param>
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

	Vector2f* GetVelocity();

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