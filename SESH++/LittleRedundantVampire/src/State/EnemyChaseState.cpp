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

EnemyChaseState::~EnemyChaseState()
{
	// Deletes range.
	delete range;
	range = nullptr;
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
	//TODO: tjek om det er nok ikke at kalde destructoren -> Kenneth: Sletter destructoren EnemyChaseState selv eller er den stadig p� heapen??
	// Changes the state to idle.
	this->enemy->SetContext(new EnemyIdleState());
	//TODO: Will this delete work? does it self-destroy and release the memory properly. 
	delete this;
}