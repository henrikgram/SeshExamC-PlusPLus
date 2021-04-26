#include "Player.h"


Player::Player(Texture* texture, Vector2u imageCount, float switchTime, float speed) : 
	//Her opretter vi en animation med de parametre som er gældende for Player.
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	faceRight = true;
	moving = false;

	//Definer størrelsen af én sprite fra sheet.
    body.setSize(Vector2f(texture->getSize().x / 4, texture->getSize().y / 3));
	body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(100.0f, 100.0f);
    //Vi sætter player-variablens til at have vores texture.
    body.setTexture(texture);
}

Player::~Player()
{
}


void Player::Update(float deltaTime)
{
	//Bestemmer hvilken retning du bevæger dig.
	Vector2f movement(0.0f, 0.0f);

	//Bestemmer hvilken retning du skal ændre til baseret på input fra keyboard.
	if (Keyboard::isKeyPressed(Keyboard::A))
		movement.x -= speed * deltaTime;
	if (Keyboard::isKeyPressed(Keyboard::D))
		movement.x += speed * deltaTime;
	if (Keyboard::isKeyPressed(Keyboard::W))
		movement.y -= speed * deltaTime;
	if (Keyboard::isKeyPressed(Keyboard::S))
		movement.y += speed * deltaTime;


	//Her indstiller man idle animation når du står stille.
	if (movement.x == 0.0f && movement.y == 0.0f)
	{
		//Bruges til at sørge for, at den rigtige sprite tegnes når vi står stille.
		moving = false;
	}
	//Start en walk cycle.
	else
	{
		moving = true;

		//Højre
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
	}

	//Vi kan nu opdatere og tegne.
	animation.Update(row, deltaTime, faceRight, moving);
	body.setTextureRect(animation.TextureRect);
	body.move(movement);
}

void Player::Draw(RenderWindow& window)
{
	window.draw(body);
}

void Player::Normalize(Vector2f& movement)
{
	//Vi udregner hypotenusen af bevægelsesretningen.
	float movementVectorLength = sqrt(movement.x * movement.x + movement.y * movement.y);

	//Vi normaliserer retningen ift til hypotenusens længde.
	movement.x /= movementVectorLength;
	movement.y /= movementVectorLength;
}
