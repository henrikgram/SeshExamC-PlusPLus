#include "EnemyChaseState.h"

void EnemyChaseState::ChasePlayer()
{
	if (this->enemy->target->GetPosition()->x < this->enemy->gameObject->GetPosition()->x)
	{
		this->enemy->Move(Vector2f(-0.1f, 0.0f));
	}
	if (this->enemy->target->GetPosition()->x > this->enemy->gameObject->GetPosition()->x)
	{
		this->enemy->Move(Vector2f(0.1f, 0.0f));
	}
	if (this->enemy->target->GetPosition()->y < this->enemy->gameObject->GetPosition()->y)
	{
		this->enemy->Move(Vector2f(0.0f, -0.1f));
	}
	if (this->enemy->target->GetPosition()->y > this->enemy->gameObject->GetPosition()->y)
	{
		this->enemy->Move(Vector2f(0.0f, 0.1f));
	}
}

void EnemyChaseState::Enter(Enemy* enemy)
{
	this->enemy = enemy;
	*range = 300;
}

void EnemyChaseState::Execute()
{
	ChasePlayer();

	// If the player goes out of range, we run Exit();
	if (this->enemy->targetDistance->x < -*range || this->enemy->targetDistance->x > *range ||
		this->enemy->targetDistance->y < -*range || this->enemy->targetDistance->y > *range)
	{
		Exit();
	}
}

void EnemyChaseState::Exit()
{
	// Deletes range.
	range = nullptr;
	delete range;

	// Changes the state to idle.
	this->enemy->SetContext(new EnemyIdleState());

	// Makes sure to delete the enemy.
	this->enemy = nullptr;
	delete this->enemy;
}