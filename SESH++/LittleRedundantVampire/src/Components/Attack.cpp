#include "Attack.h"
#include "AttackFactory.h"
#include "SpriteRenderer.h"
#include "../GameWorld.h"
#include <iostream>
using namespace std;
using namespace sf;


Attack::Attack(ObjectTag tag, Vector2f callerPosition, string direction)
{
	this->tag = new ObjectTag();
	*this->tag = tag;

	this->callerPosition = new Vector2f();
	*this->callerPosition = callerPosition;

	this->direction = new string();
	*this->direction = direction;

	CreateAttack();
}

Attack::~Attack()
{
	delete tag;
	tag = nullptr;

	delete callerPosition;
	callerPosition = nullptr;

	delete direction;
	direction = nullptr;
}

void Attack::Awake()
{
	//attackLength = 0.5f;
}

void Attack::Start()
{

}

void Attack::CreateAttack()
{
	SpriteRenderer* sr = new SpriteRenderer();
	gameObject = new GameObject();

	sr->SetSprite(TextureTag::ATTACK_SHEET);
	gameObject->AddComponent(sr);

	gameObject->Awake();
	gameObject->Start();

	(*GameWorld::GetInstance()->GetGameObjects()).push_back(gameObject);
}

void Attack::StartAttack()
{

}

void Attack::Update(Time* timePerFrame)
{
	attackTimer += timePerFrame->asMilliseconds();

	//if (attackTimer >= attackLength)
	//{
		//Bestemmer hvilken retning du skal aendre til baseret paa input fra keyboard.
		//TODO: Change so that it's not based on keyboard inputs.
		//Venstre
		if (*direction == "left")
		{
			*gameObject->position = Vector2f((*callerPosition).x - 60.0f, (*callerPosition).y);
			//sprite skal også ændres her somehow.
		}
		//Hoejre
		else if (*direction == "right")
		{
			*gameObject->position = Vector2f((*callerPosition).x + 60.0f, (*callerPosition).y);
			//sprite skal også ændres her somehow.
		}
		//Op
		else if (*direction == "up")
		{
			*gameObject->position = Vector2f((*callerPosition).x, (*callerPosition).y - 70.0f);
			//sprite skal også ændres her somehow.
		}
		//Ned
		else if (*direction == "down")
		{
			*gameObject->position = Vector2f((*callerPosition).x, (*callerPosition).y + 70.0f);
			//sprite skal også ændres her somehow.
		}
	//}

	////Her angriber spilleren.
	////TODO: make this based on an attack event.
	//if (Keyboard::isKeyPressed(Keyboard::Space))
	//{
	//	attackTimer = 0.0f;
	//	gameObject->shouldDraw = true;
	//}
	//else
	//{
	//	gameObject->shouldDraw = false;
	//}
}

void Attack::Destroy()
{

}

ComponentTag Attack::ToEnum()
{
	return ComponentTag::ATTACK;
}
