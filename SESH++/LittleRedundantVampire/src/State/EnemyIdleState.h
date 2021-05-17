#pragma once
#include "IState.h"
#include "ContextState.h"
//#include "../Components/Enemy.h"

class EnemyIdleState : public IState
{
private:
	GameObject* enemy = new GameObject();
	void Patrol();

public:
	// Inherited via IState
	virtual void Enter(GameObject* go) override;
	virtual void Execute() override;
	virtual void Exit() override;
};