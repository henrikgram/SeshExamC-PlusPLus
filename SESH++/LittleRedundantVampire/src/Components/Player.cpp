
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

void Player::Awake()
{
	
}


void Player::Start()
{

}

void Player::Update(Time* timePerFrame)
{
	
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
		//cout << "hit npc";
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
