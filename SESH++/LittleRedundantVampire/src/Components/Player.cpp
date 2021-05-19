
#include "Player.h"
#include <iostream>
#include "../GameWorld.h"
#include "AnimationComponent.h"

using namespace std;
using namespace sf;

Player::Player()
{
	health = new int;
	*health = 10;

	healthBar = new GameObject();
	srHealthBar = new SpriteRenderer();

	timer = 0.0f;
	invincibilityTimer = 0.0f;

	invincible = false;
	damageTaken = false;
}

Player::~Player()
{
	delete healthBar;
	healthBar = nullptr;

	delete srHealthBar;
	srHealthBar = nullptr;

	delete health;
	health = nullptr;
}

void Player::Awake()
{
	srHealthBar->isSpriteSheet = true;
	srHealthBar->currentImage = new Vector2u(1, 1);
	srHealthBar->imageCount = new Vector2u(1, 10);

	srHealthBar->SetSprite(TextureTag::PLAYER_HEALTH);
	healthBar->AddComponent(srHealthBar);

	AnimationComponent* aC = new AnimationComponent(srHealthBar, *srHealthBar->imageCount, 200.0f, 0);
	healthBar->AddComponent(aC);

	SpriteRenderer& srRef = *srHealthBar;
	AnimationController* acController = new AnimationController(srRef, health, *health);
	healthBar->AddComponent(acController);
	acController->ChangeAnimation.Attach(aC);

	healthBar->Awake();
	healthBar->Start();

	*healthBar->GetShouldDraw() = false;

	(*GameWorld::GetInstance()->GetGameObjects()).push_back(healthBar);
}


void Player::Start()
{

}

void Player::Update(Time* timePerFrame)
{
	*healthBar->GetPosition() = Vector2f((*gameObject->GetPosition()).x, (*gameObject->GetPosition()).y - 75);


	////Delete later, only for healthbar testing.
	//timer += timePerFrame->asMilliseconds();
	//if (timer >= 1000.0f)
	//{
	//	--*health;
	//	timer = 0.0f;
	//}


	//Checks damage.
	if (damageTaken)
	{
		invincible = true;
		--*health;

		damageTaken = false;
		*healthBar->GetShouldDraw() = true;
	}

	if (invincible)
	{
		invincibilityTimer += timePerFrame->asMilliseconds();

		if (invincibilityTimer >= 1000.0f)
		{
			invincible = false;
			*healthBar->GetShouldDraw() = false;

			invincibilityTimer = 0.0f;
		}
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
		if (!invincible)
		{
			damageTaken = true;
		}
		break;
	case ObjectTag::PLAYERATTACK:
		break;
	case ObjectTag::ENEMYATTACK:
		if (!invincible)
		{
			damageTaken = true;
		}
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
