#include "../Headers/Components/Movement.h"

Movement::Movement(float speed, Vector2f velocity)
{
	this->speed = new float(speed);
	this->velocity = new Vector2f(velocity);
}

Movement::~Movement()
{
	delete speed;
	speed = nullptr;
	delete velocity;
	velocity = nullptr;
}

void Movement::Awake()
{
}

void Movement::Start()
{
}

void Movement::Update(Time* timePerFrame)
{
}

void Movement::Destroy()
{
}

ComponentTag Movement::ToEnum()
{
	return ComponentTag();
}

void Movement::Move()
{
}

void Movement::Normalize()
{
}
