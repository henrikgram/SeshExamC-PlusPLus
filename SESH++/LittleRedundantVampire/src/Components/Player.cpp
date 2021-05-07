
#include "Player.h"
#include "../Enum/ObjectTag.h"
#include <iostream>
using namespace std;
using namespace sf;

Player::~Player()
{

}

void Player::Move(Vector2f velocity)
{
	this->velocity += velocity;
}

void Player::Awake()
{
	//attack = new Attack(ObjectTag::PLAYER, Vector2f(gameObject->position->x, gameObject->position->y), direction);
	speed = 5.0f;
	velocity = Vector2f(0.0f, 0.0f);
}

void Player::Start()
{

}

void Player::Update(Time* timePerFrame)
{
	Normalize();
}

void Player::Normalize()
{
	if (velocity != Vector2f(0.0f, 0.0f))
	{
		//Vi udregner hypotenusen af bevaegelsesretningen.
		float movementVectorLength = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);

		//Vi normaliserer retningen ift til hypotenusens laengde.
		velocity.x /= movementVectorLength;
		velocity.y /= movementVectorLength;

		velocity.x *= speed;
		velocity.y *= speed;

		//cout << velocity.x << " : " << velocity.y << "\n";
		*gameObject->position += velocity;
		velocity = Vector2f(0.0f, 0.0f);
	}
}

void Player::Destroy()
{

}

ComponentTag Player::ToEnum()
{
	return ComponentTag::PLAYER;
}
