#include "Enemy.h"

Enemy::Enemy()
{
    //*speed = 5.0f;
    //*velocity = Vector2f(0.0f, 0.0f);
}

Enemy::~Enemy()
{
    //delete currentState;
    //delete this;
}

void Enemy::Awake()
{
	*speed = 5.0f;
	*velocity = Vector2f(0.0f, 0.0f);
    currentState = new ContextState(new EnemyIdleState());
}

void Enemy::Start()
{
    currentState->StartRequest(this);
}

void Enemy::Update(Time* timePerFrame)
{
	Normalize();
}

void Enemy::Destroy()
{

}

void Enemy::Move(Vector2f velocity)
{
	(*this->velocity) += velocity;
}

ComponentTag Enemy::ToEnum()
{
    return ComponentTag::ENEMY;
}

float Enemy::GetSpeed()
{
    return *speed;
}

void Enemy::SetSpeed(float newSpeed)
{
    *speed = newSpeed;
}

Vector2f Enemy::GetVelocity()
{
    return *velocity;
}

void Enemy::SetVelocity(Vector2f newVelocity)
{
    *velocity = newVelocity;
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