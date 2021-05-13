
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
	ChangeAnimation.Notify("1",this);
	this->velocity += velocity;
}

void Player::Awake()
{
	//attack = new Attack(ObjectTag::PLAYER, Vector2f(gameObject->position->x, gameObject->position->y), direction);
	speed = 5.0f;
	velocity = Vector2f(0.0f, 0.0f);
}

void Player::UpdateAnimation()
{
	//TODO: OPTIMERING fix så den ikke kører medmindre det er en ny animation. OPTIMERING
	if (velocity.x == 0 && velocity.y == 0)
	{
		ChangeAnimation.Notify("3", this);
	}
	else if (velocity.y < 0)
	{
		ChangeAnimation.Notify("2", this);
	}
	else if (velocity.y > 0)
	{
		ChangeAnimation.Notify("0", this);
	}
	else if (velocity.x < 0)
	{
		if (!flipped)
		{
			ChangeAnimation.Notify("1", this);
			ChangeAnimation.Notify("flip",this);
			flipped = true;
		}
	}

	else if (velocity.x > 0)
	{
		if (flipped)
		{
			ChangeAnimation.Notify("1", this);
			ChangeAnimation.Notify("flip",this);
			flipped = false;
		}
	}

}

void Player::Start()
{

}

void Player::Update(Time* timePerFrame)
{
	UpdateAnimation();

	Normalize();

	if (speed < 5.0f)
	{
		speed++;
	}
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

		//TODO: OPTIMERING: implementer funktioanlitet i commmand pattern så den registrerer når man slipper en tast, og sætter vector til 0 frem for her
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

void Player::OnNotifyCollision(ObjectTag otherTag, std::string side)
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
		//speed = 0.9f;
		//cout << "I hit a crate";
		/*if (side == "Left")
		{
			velocity.x -= 0.1f;
		}
		if (side == "Right")
		{
			velocity.x += 0.1f;
		}
		if (side == "Top")
		{
			velocity.y -= 0.1f;
		}
		if (side == "Bottom")
		{
			velocity.y += 0.1f;
		}*/
		break;
	default:
		break;
	}
}
