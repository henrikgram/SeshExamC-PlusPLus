#ifndef  ENEMYCHASESTATE_H
#define ENEMYCHASESTATE_H

#include "IState.h"
#include "../Components/Enemy.h"

class EnemyChaseState : public IState
{
private:
	Enemy* enemy;
	// Determines the enemy's range.
	int* range = new int();

	/// <summary>
	/// Method to get the enemy to chase the player when within range.
	/// </summary>
	void ChasePlayer();

public:
	~EnemyChaseState();

	// Inherited via IState
	virtual void Enter(Enemy* enemy) override;
	virtual void Execute() override;
	virtual void Exit() override;
};

#endif