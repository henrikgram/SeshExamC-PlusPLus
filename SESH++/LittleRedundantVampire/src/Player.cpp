#include "Player.h"

Player::Player(Texture* texture, Vector2u imageCount, float switchTime, float speed) : 
	//Her opretter vi en animation med de parametre som er g�ldende for Player.
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	faceRight = true;

	//Definer st�rrelsen af �n sprite fra sheet.
    body.setSize(Vector2f(texture->getSize().x / 4, texture->getSize().y / 3));
    body.setPosition(100.0f, 100.0f);
    //Vi s�tter player-variablens til at have vores texture.
    body.setTexture(texture);
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	//Bestemmer hvilken retning du bev�ger dig.
	Vector2f movement(0.0f, 0.0f);

	//Bestemmer hvilken retning du skal �ndre til baseret p� input fra keyboard.
	if (Keyboard::isKeyPressed(Keyboard::A))
		movement.x -= speed * deltaTime;
	if (Keyboard::isKeyPressed(Keyboard::D))
		movement.x += speed * deltaTime;
	if (Keyboard::isKeyPressed(Keyboard::W))
		movement.y -= speed * deltaTime;
	if (Keyboard::isKeyPressed(Keyboard::S))
		movement.y += speed * deltaTime;


	//Her indstiller man idle animation n�r du st�r stille.
	if (movement.x == 0.0f && movement.y == 0.0f)
	{
		//Her skal man bruge den r�kke som er idle animation.
		row = 0;
	}
	//Start en walk cycle.
	else
	{
		//H�jre
		if (movement.x > 0.0f)
		{
			faceRight = true;
			row = 1;
		}
		//Venstre
		else if (movement.x < 0.0f)
		{
			faceRight = false;
			row = 1;
		}
		//Ned
		else if (movement.y > 0.0f)
		{
			row = 0;
		}
		//Op
		else if (movement.y < 0.0f)
		{
			row = 2;
		}

		//Vi kan nu opdatere og tegne.
		animation.Update(row, deltaTime, faceRight);
		body.setTextureRect(animation.textureRect);
		body.move(movement);
	}
}

void Player::Draw(RenderWindow& window)
{
	window.draw(body);
}
