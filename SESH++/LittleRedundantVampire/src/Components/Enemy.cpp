#include "Enemy.h"
#include "../GameWorld.h"


//TODO: check dem som er uninitialized.
Enemy::Enemy()
{
	speed = new float();
	velocity = new Vector2f();
}

Enemy::~Enemy()
{
	targetDistance = nullptr;
	delete targetDistance;

	currentState = nullptr;
	delete currentState;

	velocity = nullptr;
	delete velocity;

	target = nullptr;
	delete target;

	speed = nullptr;
	delete speed;

	velocity = nullptr;
	delete velocity;

	delete this;
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

	// TODO: Change once player has been moved into LM. This is shit.
	if (target == nullptr)
	{
		TempUntilPlayerIsMovedIntoLM();
	}
	else
	{
		PlayerDistance();
	}
}

void Enemy::Destroy()
{
}

void Enemy::Move(Vector2f velocity)
{
	(*this->velocity) += velocity;
}

void Enemy::TempUntilPlayerIsMovedIntoLM()
{
	vector<GameObject*>::size_type gameObjectsSize = (*GameWorld::GetInstance()->GetGameObjects()).size();

	//iterates through the gameObjects.
	for (vector<GameObject*>::size_type i = 0; i < gameObjectsSize; ++i)
	{
		GameObject* go = (*GameWorld::GetInstance()->GetGameObjects())[i];

		if (*go->GetObjectTag() == ObjectTag::PLAYER)
		{
			// Once the player has been found, target becomes player.
			target = go;
		}
	}
}

void Enemy::PlayerDistance()
{
	targetDistance->x = target->GetPosition()->x - this->gameObject->GetPosition()->x;
	targetDistance->y = target->GetPosition()->y - this->gameObject->GetPosition()->y;
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

ContextState Enemy::GetContext()
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

		*gameObject->GetPosition() += *velocity;

		//TODO: OPTIMERING:
		*velocity = Vector2f(0.0f, 0.0f);
	}
}