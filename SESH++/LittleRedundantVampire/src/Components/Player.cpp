
#include "Player.h"
#include "../Enum/ObjectTag.h"
#include <iostream>
using namespace std;
using namespace sf;

Player::Player()
{

}

Player::~Player()
{

}

void Player::Move(Vector2f velocity)
{
	this->velocity += velocity;
}


void Player::Awake()
{
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
		*gameObject->GetPosition() += velocity;
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

void Player::NotifyCollision(ObjectTag otherTag)
{
	switch (otherTag)
	{
	case ObjectTag::PLAYER:
		break;
	case ObjectTag::ENEMY:
		break;
	case ObjectTag::PLAYERATTACK:
		break;
	case ObjectTag::ENEMYATTACK:
		break;
	case ObjectTag::NPC:
		break;
	case ObjectTag::WALL:
		break;
	case ObjectTag::WALL_DECORATION:
		break;
	case ObjectTag::WINDOW:
		break;
	case ObjectTag::WINDOW_DECORATION:
		break;
	case ObjectTag::DOOR:
		break;
	case ObjectTag::FLOOR_CARPET:
		break;
	case ObjectTag::FLOOR_WOOD:
		break;
	case ObjectTag::BOOKCASE:
		break;
	case ObjectTag::VASE:
		break;
	case ObjectTag::KEY:
		break;
	case ObjectTag::CHEST:
		break;
	case ObjectTag::CRATE:
		cout << "I hit a crate";
		break;
	default:
		break;
	}
}
