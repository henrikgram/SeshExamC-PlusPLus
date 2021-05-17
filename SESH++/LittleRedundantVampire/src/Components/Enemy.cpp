#include "Enemy.h"

Enemy::Enemy()
{
    speed = float(5.0f);
    velocity = Vector2f(0.0f, 0.0f);
}

Enemy::~Enemy()
{
    //delete currentState;
    //delete this;
}

void Enemy::Awake()
{
    currentState = new ContextState(new EnemyIdleState());
}

void Enemy::Start()
{
    currentState->StartRequest();
}

void Enemy::Update(Time* timePerFrame)
{
}

void Enemy::Destroy()
{

}

ComponentTag Enemy::ToEnum()
{
    return ComponentTag::ENEMY;
}

float Enemy::GetSpeed()
{
    return speed;
}

void Enemy::SetSpeed(float newSpeed)
{
    speed = newSpeed;
}

Vector2f Enemy::GetVelocity()
{
    return velocity;
}

void Enemy::SetVelocity(Vector2f newVelocity)
{
    velocity = newVelocity;
}
