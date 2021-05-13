#include "Attack.h"
#include "AttackSpawner.h"
#include "SpriteRenderer.h"
#include "../GameWorld.h"
#include <iostream>
using namespace std;
using namespace sf;


Attack::Attack(ObjectTag objectTag, Vector2f callerPosition, string direction, float attackLength)
{
	this->direction = new string;
	*this->direction = direction;

	this->objectTag = new ObjectTag;
	*this->objectTag = objectTag;

	this->callerPosition = new Vector2f;
	*this->callerPosition = callerPosition;

	attackTimer = new float;

	this->attackLength = new float;
	*this->attackLength = attackLength;
}

Attack::~Attack()
{
	delete objectTag;
	objectTag = nullptr;

	delete callerPosition;
	callerPosition = nullptr;

	delete attackTimer;
	attackTimer = nullptr;

	delete attackLength;
	attackLength = nullptr;

	delete direction;
	direction = nullptr;
}


void Attack::Awake()
{
	*gameObject->GetPosition() = *callerPosition;
	*attackTimer = 0.0f;
}

void Attack::Start()
{
	//TODO: Det her skal kunne fungere med events, der kører når spilleren bevæger sig.
	//Left
	if (*direction == "left")
	{
		*gameObject->GetPosition() = Vector2f((*gameObject->GetPosition()).x - 300.0f, (*gameObject->GetPosition()).y);
	}
	//Right
	if (*direction == "right")
	{
		*gameObject->GetPosition() = Vector2f((*gameObject->GetPosition()).x + 60.0f, (*gameObject->GetPosition()).y);
	}
	//Up
	if (*direction == "up")
	{
		*gameObject->GetPosition() = Vector2f((*gameObject->GetPosition()).x, (*gameObject->GetPosition()).y - 70.0f);
	}
	//Down
	if (*direction == "down")
	{
		*gameObject->GetPosition() = Vector2f((*gameObject->GetPosition()).x, (*gameObject->GetPosition()).y + 70.0f);
	}
}

void Attack::Update(Time* timePerFrame)
{
	*attackTimer += timePerFrame->asMilliseconds();

	if (*attackTimer >= *attackLength)
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
