#include "../Headers/Components/Attack.h"
#include <iostream>
using namespace std;
using namespace sf;


Attack::Attack(Vector2f callerPosition, string direction)
{
	this->callerPosition = callerPosition;
	this->direction = direction;
}

Attack::~Attack()
{

}

void Attack::Awake()
{
	attackLength = 0.5f;
	gameObject->shouldDraw = false;
}

void Attack::Start()
{

}

void Attack::Update(Time* timePerFrame)
{
	attackTimer += timePerFrame->asMilliseconds();

	if (attackTimer >= attackLength)
	{
		//Bestemmer hvilken retning du skal aendre til baseret paa input fra keyboard.
		//TODO: Change so that it's not based on keyboard inputs.
		//Venstre
		if (direction == "left")
		{
			*gameObject->position = Vector2f(callerPosition.x - 60.0f, callerPosition.y);
			//sprite skal også ændres her somehow.
		}
		//Hoejre
		else if (direction == "right")
		{
			*gameObject->position = Vector2f(callerPosition.x + 60.0f, callerPosition.y);
			//sprite skal også ændres her somehow.
		}
		//Op
		else if (direction == "up")
		{
			*gameObject->position = Vector2f(callerPosition.x, callerPosition.y - 70.0f);
			//sprite skal også ændres her somehow.
		}
		//Ned
		else if (direction == "down")
		{
			*gameObject->position = Vector2f(callerPosition.x, callerPosition.y + 70.0f);
			//sprite skal også ændres her somehow.
		}
	}

	//Her angriber spilleren.
	//TODO: make this based on an attack event.
	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		attackTimer = 0.0f;
		gameObject->shouldDraw = true;
	}
	else
	{
		gameObject->shouldDraw = false;
	}
}

void Attack::Destroy()
{

}

ComponentTag Attack::ToEnum()
{
	return ComponentTag::ATTACK;
}
