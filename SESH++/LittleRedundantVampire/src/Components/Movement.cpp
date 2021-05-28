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

		// We normalize the direction in regards to the length of the hypotenuse, so that no matter which direction we walk in the velocity vector will
		// always have the same length.
		velocity->x /= movementVectorLength;
		velocity->y /= movementVectorLength;

		velocity->x *= speed;
		velocity->y *= speed;

		*gameObject->GetPosition() += *velocity;
		//After updating the gameObjects position we set the velocity to 0 again so the gameObject doesn't keep travelling in the same direction indefinately,
		//since this method is called in Update.
		*velocity = Vector2f(0.0f, 0.0f);
	}
}

Vector2f* Movement::GetVelocity()
{
	return velocity;
}