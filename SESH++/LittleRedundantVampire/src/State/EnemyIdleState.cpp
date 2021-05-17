#include "EnemyIdleState.h"

void EnemyIdleState::Patrol()
{
	cout << " F ";
	*enemy->move
}

void EnemyIdleState::Enter(GameObject* go)
{
	this->enemy = go;
	Execute();
}

void EnemyIdleState::Execute()
{
	Patrol();
	//Exit();
}

void EnemyIdleState::Exit()
{
	//ContextState* context = new ContextState(new EnemyIdleState());
	this->SetContext(context);
	delete this;
}
