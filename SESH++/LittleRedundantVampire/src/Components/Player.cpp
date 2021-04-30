#include "../Headers/Components/Player.h"
#include <iostream>
using namespace std;
using namespace sf;

Player::~Player()
{

}

void Player::Awake()
{
	speed = 5.0f;
}

void Player::Start()
{

}

void Player::Update(Time* timePerFrame)
{
	//Bestemmer hvilken retning du bevaeger dig.
	Vector2f movement(0.0f, 0.0f);


	//Bestemmer hvilken retning du skal aendre til baseret paa input fra keyboard.
	//Venstre
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		movement.x -= timePerFrame->asMilliseconds();
	}
	//Hoejre
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		movement.x += timePerFrame->asMilliseconds();
	}
	//Op
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		movement.y -= timePerFrame->asMilliseconds();
	}
	//Ned
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		movement.y += timePerFrame->asMilliseconds();
	}

	//Vi udregner hypotenusen af bevaegelsesretningen.
	float movementVectorLength = sqrt(movement.x * movement.x + movement.y * movement.y);

	//Vi normaliserer retningen ift til hypotenusens laengde.
	if (movement != Vector2f(0.0f, 0.0f))
	{
		Normalize(movement);
	}


	*gameObject->position += movement;
}

void Player::Normalize(Vector2f& movement)
{
	//Vi udregner hypotenusen af bevaegelsesretningen.
	float movementVectorLength = sqrt(movement.x * movement.x + movement.y * movement.y);

	//Vi normaliserer retningen ift til hypotenusens laengde.
	movement.x /= movementVectorLength;
	movement.y /= movementVectorLength;

	movement.x *= speed;
	movement.y *= speed;
}

void Player::Destroy()
{

}

ComponentTag Player::ToEnum()
{
	return ComponentTag::PLAYER;
}
