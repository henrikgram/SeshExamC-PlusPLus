#pragma once
#include "IState.h"
#include "ContextState.h"
#include "../Components/Enemy.h"

class EnemyIdleState : public IState
{
private:
	//Enemy en;
	void Patrol();

public:
	// Inherited via IState
	virtual void Enter() override;
	virtual void Execute() override;
	virtual void Exit() override;
};