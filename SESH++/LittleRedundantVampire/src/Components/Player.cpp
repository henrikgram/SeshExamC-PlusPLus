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
	srHealthBar = new SpriteRenderer(TextureTag::PLAYER_HEALTH, Vector2u(1, 1), Vector2u(1, 10));


	invincibilityTimer = 0.0f;

	invincible = false;
	damageTaken = false;
}

Player::~Player()
{
	delete health;
	health = nullptr;
}

void Player::Awake()
{
	//Creates the healthbar.
	healthBar->AddComponent(srHealthBar);

	AnimationComponent* aC = new AnimationComponent(srHealthBar, srHealthBar->GetImageCount(), 200.0f, 0);
	healthBar->AddComponent(aC);

	SpriteRenderer& srRef = *srHealthBar;
	AnimationController* acController = new AnimationController(srRef, health, *health);
	healthBar->AddComponent(acController);
	acController->AttachListenerToChangeAnimation(aC);

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
	//Manages the health bar.
	*healthBar->GetPosition() = Vector2f((*gameObject->GetPosition()).x, (*gameObject->GetPosition()).y - 75);

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
	Player::~Player();
}

ComponentTag Player::ToEnum()
{
	return ComponentTag::PLAYER;
}

void Player::OnNotifyCollision(ObjectTag otherTag, std::string side)
{
	switch (otherTag)
	{
	case ObjectTag::ENEMY:
		if (!invincible)
		{
			damageTaken = true;
		}
		break;
	case ObjectTag::ENEMYATTACK:
		if (!invincible)
		{
			damageTaken = true;
		}
		break;
	default:
		break;
	}
	//TOOD: ryddes op her
}
