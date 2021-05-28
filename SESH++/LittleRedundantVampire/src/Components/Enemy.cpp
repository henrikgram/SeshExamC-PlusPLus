#include "Enemy.h"
#include "../GameWorld.h"


Enemy::Enemy()
{
	targetDistance = new Vector2f(0, 0);
	speed = new float();
	velocity = new Vector2f();
}

Enemy::~Enemy()
{
	delete targetDistance;
	targetDistance = nullptr;

	delete currentState;
	currentState = nullptr;

	delete speed;
	speed = nullptr;

	delete velocity;
	velocity = nullptr;
}

void Enemy::Awake()
{
	*speed = 1.0f;
	// All enemies are initialized in idle-state.
	currentState = new ContextState(new EnemyIdleState());
}

void Enemy::Start()
{
	// Makes sure to run Enter() on the first state.
	currentState->StartRequest(this);
}

void Enemy::Update(Time* timePerFrame)
{
	Normalize();
	// This runs Execute() on the current state.
	currentState->RunRequest();

	PlayerDistance();
}

void Enemy::Destroy()
{

	Enemy::~Enemy();

}

void Enemy::Move(Vector2f velocity)
{
	(*this->velocity) += velocity;
}

void Enemy::SetTarget(GameObject* target)
{
	this->target = target;
}

void Enemy::OnNotifyCollision(ObjectTag otherTag, std::string side)
{
	if (otherTag == ObjectTag::PLAYERATTACK)
	{
		gameObject->CallSelfDestruct();
	}
}

void Enemy::PlayerDistance()
{
	targetDistance->x = target->GetPosition().x - this->gameObject->GetPosition().x;
	targetDistance->y = target->GetPosition().y - this->gameObject->GetPosition().y;
}

ComponentTag Enemy::ToEnum()
{
	return ComponentTag::ENEMY;
}

void Enemy::SetSpeed(float newSpeed)
{
	*speed = newSpeed;
}

void Enemy::SetContext(IState* state)
{
	currentState->TransitionTo(state);
	currentState->StartRequest(this);
}

ContextState Enemy::GetContext() const
{
	return *currentState;
}

void Enemy::Normalize()
{
	if (*velocity != Vector2f(0.0f, 0.0f))
	{
		float movementVectorLength = sqrt(velocity->x * velocity->x + velocity->y * velocity->y);

		velocity->x /= movementVectorLength;
		velocity->y /= movementVectorLength;

		velocity->x *= *speed;
		velocity->y *= *speed;

		gameObject->SetPosition(gameObject->GetPosition() + *velocity);

		//TODO:* OPTIMIZE Use MoveCompoennt here:
		//Can be implemented as moveComponent later
		*velocity = Vector2f(0.0f, 0.0f);
	}
}