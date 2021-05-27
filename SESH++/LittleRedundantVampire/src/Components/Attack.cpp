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
	switch (*gameObject->GetDirection())
	{
	case 'N':
		(*gameObject->GetPosition()).y += 80.0f;
		break;
	case 'L':
		(*gameObject->GetPosition()).x -= 70.0f;
		break;
	case 'R':
		(*gameObject->GetPosition()).x += 70.0f;
		break;
	case 'U':
		(*gameObject->GetPosition()).y -= 80.0f;
		break;
	case 'D':
		(*gameObject->GetPosition()).y += 80.0f;
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
		//TODO: EMMA Make sure object gets deleted here instead.
		*gameObject->GetShouldDraw() = false;
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
