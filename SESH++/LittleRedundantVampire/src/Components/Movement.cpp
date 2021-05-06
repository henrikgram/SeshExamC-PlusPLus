#include "Movement.h"

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
	Normalize();
}

void Movement::Destroy()
{
}

ComponentTag Movement::ToEnum()
{
	return ComponentTag();
}

void Movement::Move(Vector2f velocity)
{
	(*this->velocity) += velocity;
}

void Movement::Normalize()
{
	if (*velocity != Vector2f(0.0f, 0.0f))
	{
		//Vi udregner hypotenusen af bevaegelsesretningen.
		float movementVectorLength = sqrt(velocity->x * velocity->x + velocity->y * velocity->y);

		//Vi normaliserer retningen ift til hypotenusens laengde.
		velocity->x /= movementVectorLength;
		velocity->y /= movementVectorLength;

		velocity->x *= *speed;
		velocity->y *= *speed;

		cout << velocity->x << " : " << velocity->y << "\n";
		*gameObject->position += *velocity;
		*velocity = Vector2f(0.0f, 0.0f);
	}
}
