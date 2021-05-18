#pragma once
#include "IState.h"
#include "ContextState.h"

#ifndef  ENEMYIDLYSTATE_H
#define ENEMYIDLYSTATE_H_H
class Enemy;
class EnemyIdleState : public IState
{
private:
	Enemy* enemy;
	void Patrol();

public:
	// Inherited via IState
	virtual void Enter(Enemy* enemy) override;
	virtual void Execute() override;
	virtual void Exit() override;
};

#endif