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

	//Manage which direction is moved towards.
	//No walking
	if ((*velocity).x == 0 && (*velocity).y == 0)
	{
		gameObject->SetDirection('N');
	}
	//Up
	if ((*velocity).y < 0)
	{
		gameObject->SetDirection('U');
	}

	//Down
	if ((*velocity).y > 0)
	{
		gameObject->SetDirection('D');
	}

	//Left
	if ((*velocity).x < 0)
	{
		gameObject->SetDirection('L');
	}

	//Right
	if ((*velocity).x > 0)
	{
		gameObject->SetDirection('R');
	}

	Normalize();
}

void Movement::Destroy()
{
	Movement::~Movement();
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
		// We calculate the hypotenuse of the movement direction.
		float movementVectorLength = sqrt(velocity->x * velocity->x + velocity->y * velocity->y);

		// We normalize the direction in regards to the length of the hypotenuse.
		velocity->x /= movementVectorLength;
		velocity->y /= movementVectorLength;

		velocity->x *= speed;
		velocity->y *= speed;

		//TODO: SIGNE STINNA check her
		//*gameObject->GetPosition() += *velocity;
		gameObject->SetPosition(gameObject->GetPosition() + *velocity);
		*velocity = Vector2f(0.0f, 0.0f);
	}
}

Vector2f* Movement::GetVelocity()
{
	return velocity;
}