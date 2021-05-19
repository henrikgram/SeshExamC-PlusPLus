#include "Movement.h"

Movement::Movement(float speed, Vector2f velocity)
{
	this->speed = speed;
	this->velocity = new Vector2f(velocity);
}

Movement::~Movement()
{
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
	if (speed < 5.0f)
	{
		++speed;
	}

	//No walking
	if ((*velocity).x == 0 && (*velocity).y == 0)
	{
		*gameObject->GetDirection() = 'N';
	}
	//Up
	if ((*velocity).y < 0)
	{
		*gameObject->GetDirection() = 'U';
	}

	//Down
	if ((*velocity).y > 0)
	{
		*gameObject->GetDirection() = 'D';
	}

	//Left
	if ((*velocity).x < 0)
	{
		*gameObject->GetDirection() = 'L';
	}

	//Right
	if ((*velocity).x > 0)
	{
		*gameObject->GetDirection() = 'R';
	}

	Normalize();
}

void Movement::Destroy()
{
}

ComponentTag Movement::ToEnum()
{
	return ComponentTag::MOVEMENT;
}

void Movement::Move(Vector2f velocity)
{
	*this->velocity += velocity;
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

		velocity->x *= speed;
		velocity->y *= speed;

		//cout << velocity->x << " : " << velocity->y << "\n";
		*gameObject->GetPosition() += *velocity;
		*velocity = Vector2f(0.0f, 0.0f);
	}
}

Vector2f* Movement::GetVelocity()
{
	return velocity;
}
