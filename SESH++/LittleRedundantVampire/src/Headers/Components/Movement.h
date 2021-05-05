#pragma once
#include "../Component.h"

class Movement : public Component
{
public:
	Movement(float speed, Vector2f velocity);
	~Movement();


	// Inherited via Component
	void Awake();

	void Start();

	void Update(Time* timePerFrame);

	void Destroy();

	ComponentTag ToEnum();

	void Move();

	void Normalize();

private:
	float* speed;
	Vector2f* velocity;
};

