#pragma once
#include "../Component.h"
#include "../State/IState.h"
#include "../State/ContextState.h"
#include "../State/EnemyIdleState.h"

class Enemy : public Component
{
public:
	Enemy();
	~Enemy();

	// Inherited via Component
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update(Time* timePerFrame) override;
	virtual void Destroy() override;
	virtual ComponentTag ToEnum() override;

	float GetSpeed();
	void SetSpeed(float newSpeed);

	Vector2f GetVelocity();
	void SetVelocity(Vector2f newVelocity);

private:
	float speed;
	Vector2f velocity;

	ContextState* currentState;
};

