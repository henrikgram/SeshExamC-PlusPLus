#include "EnemyIdleState.h"

void EnemyIdleState::Patrol()
{
	cout << " F ";

}

void EnemyIdleState::Enter()
{
	//this->en = enemy;
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
