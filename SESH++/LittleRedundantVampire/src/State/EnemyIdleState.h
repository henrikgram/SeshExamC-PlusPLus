#pragma once

#ifndef  ENEMYIDLYSTATE_H
#define ENEMYIDLYSTATE_H_H

#include "IState.h"
#include "ContextState.h"
#include "../Components/Enemy.h"

class EnemyIdleState : public IState
{
private:
	// The enemy we are currently "running" on.
	Enemy* enemy;
	// The enemy's start position.
	Vector2f* startPos = new Vector2f(0, 0);
	// How far the enemy patrols from where they started.
	float* patrolDistance = new float();
	// How close player needs to be before enemy can attack/switch state.
	int* range = new int();
	// Should the enemy walk right? If not, walk left.
	bool* walkRight = new bool();

	/// <summary>
	/// Enemy will idly patrol a limited area on the x-axis.
	/// </summary>
	void Patrol();

public:
	// Inherited via IState
	virtual void Enter(Enemy* enemy) override;
	virtual void Execute() override;
	virtual void Exit() override;
};

#endif