#include "EnemyIdleState.h"

void EnemyIdleState::Patrol()
{
	cout << " F ";

	//while (true)
	//{
	//	meh->Move(Vector2f(0.0f, 0.1f));
	//}
}

void EnemyIdleState::Enter(Enemy* enemy)
{
	this->enemy = enemy;
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
