#pragma once
#include "../Component.h"

class Movement : public Component
{
public:
	Movement(float speed, Vector2f velocity);
	~Movement();


	// Inherited via Component
	void Awake() override;

	void Start() override;

	void Update(Time* timePerFrame) override;

	void Destroy() override;

	ComponentTag ToEnum() override;

	//own methods
	void Move(Vector2f velocity);

	void Normalize();

	Vector2f* GetVelocity();


private:
	float speed;
	Vector2f* velocity;
};

