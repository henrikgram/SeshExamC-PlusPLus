#include "Attack.h"
#include "AttackSpawner.h"
#include "SpriteRenderer.h"
#include "../GameWorld.h"
#include <iostream>
using namespace std;
using namespace sf;


Attack::Attack(ObjectTag objectTag, Vector2f callerPosition, char direction, float attackLength)
{
	this->direction = direction;
	this->objectTag = objectTag;
	this->callerPosition = callerPosition;
	this->attackLength = attackLength;
}

Attack::~Attack()
{

}


void Attack::Awake()
{
	*gameObject->GetPosition() = callerPosition;
	*gameObject->GetDirection() = direction;
	attackTimer = 0.0f;
}

void Attack::Start()
{
	//TODO: Det her skal kunne fungere med events, der kører når spilleren bevæger sig.
	//Nothing
	if (*gameObject->GetDirection() == 'N')
	{
		*gameObject->GetPosition() = Vector2f((*gameObject->GetPosition()).x, (*gameObject->GetPosition()).y + 80.0f);
	}
	//Left
	else if (*gameObject->GetDirection() == 'L')
	{
		*gameObject->GetPosition() = Vector2f((*gameObject->GetPosition()).x - 100.0f, (*gameObject->GetPosition()).y);
	}
	//Right
	else if (*gameObject->GetDirection() == 'R')
	{
		*gameObject->GetPosition() = Vector2f((*gameObject->GetPosition()).x + 60.0f, (*gameObject->GetPosition()).y);
	}
	//Up
	else if (*gameObject->GetDirection() == 'U')
	{
		*gameObject->GetPosition() = Vector2f((*gameObject->GetPosition()).x, (*gameObject->GetPosition()).y - 80.0f);
	}
	//Down
	else if (*gameObject->GetDirection() == 'D')
	{
		*gameObject->GetPosition() = Vector2f((*gameObject->GetPosition()).x, (*gameObject->GetPosition()).y + 80.0f);
	}
}

void Attack::Update(Time* timePerFrame)
{
	attackTimer += timePerFrame->asMilliseconds();

	if (attackTimer >= attackLength)
	{
		//TODO: Make sure object gets deleted here instead.
		*gameObject->GetShouldDraw() = false;
	}
}

//TODO: Find a proper way to delete objects.
void Attack::Destroy()
{
	//fjern fra listen af objekter.
}

ComponentTag Attack::ToEnum()
{
	return ComponentTag::ATTACK;
}
