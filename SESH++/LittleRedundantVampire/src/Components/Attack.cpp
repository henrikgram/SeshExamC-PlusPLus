#include "Attack.h"
#include "AttackSpawner.h"
#include "SpriteRenderer.h"
#include "../GameWorld.h"
#include <iostream>
using namespace std;
using namespace sf;


Attack::Attack(ObjectTag* objectTag, Vector2f callerPosition, string direction, float attackLength)
{
	this->objectTag = new ObjectTag;
	this->objectTag = objectTag;

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
}


void Attack::Awake()
{
	*attackTimer = 0.0f;
}

void Attack::Start()
{
	//Left
	if (*gameObject->direction == "left")
	{
		*gameObject->position = Vector2f((*callerPosition).x - 60.0f, (*callerPosition).y);
	}
	//Right
	if (*gameObject->direction == "right")
	{
		*gameObject->position = Vector2f((*callerPosition).x + 60.0f, (*callerPosition).y);
	}
	//Up
	if (*gameObject->direction == "up")
	{
		*gameObject->position = Vector2f((*callerPosition).x, (*callerPosition).y - 70.0f);
	}
	//Down
	if (*gameObject->direction == "down")
	{
		*gameObject->position = Vector2f((*callerPosition).x, (*callerPosition).y + 70.0f);
	}
}

void Attack::Update(Time* timePerFrame)
{
	*attackTimer += timePerFrame->asMilliseconds();

	if (*attackTimer >= *attackLength)
	{
		Destroy();
		cout << "Object destroyed" << "\n";

		*attackTimer = 0.0f;
		*gameObject->shouldDraw = false;
	}
	else
	{
		*gameObject->shouldDraw = true;
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
