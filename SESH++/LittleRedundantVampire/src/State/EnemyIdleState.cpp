#include "EnemyIdleState.h"
#include "EnemyChaseState.h"
#include "../GameWorld.h"

void EnemyIdleState::Patrol()
{
	// If the enemy has passed their original position since entering this state,
	// they need to start walking left.
	if (this->enemy->gameObject->GetPosition()->x > startPos->x)
	{
		*walkRight = false;
	}
	// If the enemy has passed the patrol distance, they need to start walking right.
	if (this->enemy->gameObject->GetPosition()->x < (startPos->x - *patrolDistance))
	{
		*walkRight = true;
	}

	if (*walkRight)
	{
		// Patrol right.
		this->enemy->Move(Vector2f(0.1f, 0.0f));
	}
	else
	{
		// Patrol left.
		this->enemy->Move(Vector2f(-0.1f, 0.0f));
	}
}

void EnemyIdleState::Enter(Enemy* enemy)
{
	this->enemy = enemy;
	*patrolDistance = 300;
	*range = 300;
	*startPos = *this->enemy->gameObject->GetPosition();
}

void EnemyIdleState::Execute()
{
	Patrol();

	// If the Player comes within range, run Exit to switch state.
	if (this->enemy->targetDistance->x > -*range && this->enemy->targetDistance->x < *range &&
		this->enemy->targetDistance->y > -*range && this->enemy->targetDistance->y < *range)
	{
		Exit();
	}
}

void EnemyIdleState::Exit()
{
	// Removes all variables.
	patrolDistance = nullptr;
	delete patrolDistance;
	startPos = nullptr;
	delete startPos;

	// Sets the new state.
	this->enemy->SetContext(new EnemyChaseState());

	// Deletes the enemy.
	this->enemy = nullptr;
	delete this->enemy;
}