#include "Attack.h"
#include "AttackSpawner.h"
#include "SpriteRenderer.h"
#include "../GameWorld.h"
#include <iostream>

using namespace std;
using namespace sf;


Attack::Attack(ObjectTag objectTag, float attackLength)
{
	this->objectTag = objectTag;
	this->attackLength = attackLength;

	attackTimer = 0.0f;
}

Attack::~Attack()
{

}

void Attack::Awake()
{

	//Positions the attack according to the callers direction.
	switch (gameObject->GetDirection())
	{
	case 'N':
		gameObject->SetPosition(Vector2f(gameObject->GetPosition().x, gameObject->GetPosition().y + 80.0f));
		break;
	case 'L':
		gameObject->SetPosition(Vector2f(gameObject->GetPosition().x - 70.0f, gameObject->GetPosition().y));
		break;
	case 'R':
		gameObject->SetPosition(Vector2f(gameObject->GetPosition().x + 70.0f, gameObject->GetPosition().y));
		break;
	case 'U':
		gameObject->SetPosition(Vector2f(gameObject->GetPosition().x, gameObject->GetPosition().y - 80.0f));
		break;
	case 'D':
		gameObject->SetPosition(Vector2f(gameObject->GetPosition().x, gameObject->GetPosition().y + 80.0f));
		break;
	}
}

void Attack::Start()
{

}

void Attack::Update(Time* timePerFrame)
{
	attackTimer += timePerFrame->asMilliseconds();

	//Manages how long the attack is active for.
	if (attackTimer >= attackLength)
	{
		gameObject->CallSelfDestruct();
	}
}


void Attack::Destroy()
{
	Attack::~Attack();
	//Remove from the list of gameObjects.
}

ComponentTag Attack::ToEnum()
{
	return ComponentTag::ATTACK;
}
