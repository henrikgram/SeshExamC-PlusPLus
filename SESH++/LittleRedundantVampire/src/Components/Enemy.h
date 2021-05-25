#ifndef ENEMY_H
#define ENEMY_H

#include "../Component.h"
#include "../State/IState.h"
#include "../State/ContextState.h"
#include "../State/EnemyIdleState.h"
#include "Player.h"


/// <summary>
/// Component: For enemy objects.
/// </summary>
class Enemy : public Component
{
public:
	// Distance between the enemy and target (player).
	Vector2f* targetDistance; 
	// Player will become target.
	GameObject* target;

	Enemy();
	~Enemy();

	// Inherited via Component
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update(Time* timePerFrame) override;
	virtual void Destroy() override;
	virtual ComponentTag ToEnum() override;

	/// <summary>
	/// Sets the speed, in case it needs to change for certain states.
	/// However, this is currently not the case.
	/// </summary>
	/// <param name="newSpeed"></param>
	void SetSpeed(float newSpeed);

	/// <summary>
	/// Sets the current context.
	/// </summary>
	/// <param name="state"></param>
	void SetContext(IState* state);

	/// <summary>
	/// Gets the current context.
	/// </summary>
	/// <returns></returns>
	ContextState GetContext() const { return *currentState; }

	/// <summary>
	/// Method to make the enemy move.
	/// </summary>
	/// <param name="velocity"></param>
	void Move(Vector2f velocity);

	void SetTarget(GameObject* target);

private:
	float* speed;
	Vector2f* velocity;

	ContextState* currentState;

	/// <summary>
	/// Calculates the distance between the player and the enemy.
	/// </summary>
	void PlayerDistance();

	/// <summary>
	/// Makes sure the enemy doesn't move faster when moving on the x- and y-axis at the same time.
	/// Right now the enemy can only move on the y- or x-axis at a time.
	/// So for the time being, this method is unnecessary.
	/// There just wasn't time to add more movement "options" for the enemy.
	/// </summary>
	void Normalize();
};

#endif;