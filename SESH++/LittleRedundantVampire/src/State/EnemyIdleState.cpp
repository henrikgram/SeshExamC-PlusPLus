#include "EnemyIdleState.h"
#include "EnemyChaseState.h"
#include "../GameWorld.h"

void EnemyIdleState::Patrol()
{
	// If the enemy has passed their original position since entering this state,
	// they need to start walking left.
	if (enemy->gameObject->GetPosition()->x > startPos->x)
	{
		*walkRight = false;
	}
	// If the enemy has passed the patrol distance, they need to start walking right.
	if (enemy->gameObject->GetPosition()->x < (startPos->x - *patrolDistance))
	{
		*walkRight = true;
	}

	if (*walkRight)
	{
		// Patrol right.
		enemy->Move(Vector2f(0.1f, 0.0f));
	}
	else
	{
		// Patrol left.
		enemy->Move(Vector2f(-0.1f, 0.0f));
	}
}

EnemyIdleState::~EnemyIdleState()
{
// Removes all variables.

	delete range;
	range = nullptr;

	delete walkRight;
	walkRight = nullptr;

	delete patrolDistance;
	patrolDistance = nullptr;

	delete startPos;
	startPos = nullptr;
}

void EnemyIdleState::Enter(Enemy* enemy)
{
	this->enemy = enemy;
	patrolDistance = new float(300);
	range = new int(300);
	walkRight = new bool();
	startPos = new Vector2f(*this->enemy->gameObject->GetPosition());
}


void EnemyIdleState::Execute()
{
	Patrol();

	// If the Player comes within range, run Exit to switch state.
	if (enemy->targetDistance->x > -*range && enemy->targetDistance->x < *range &&
		enemy->targetDistance->y > -*range && enemy->targetDistance->y < *range)
	{
		Exit();
	}
}

void EnemyIdleState::Exit()
{
	// Sets the new state.
	// TODO: Kenneth: samme problem som i chase state.
	enemy->SetContext(new EnemyChaseState());

	delete this;
}