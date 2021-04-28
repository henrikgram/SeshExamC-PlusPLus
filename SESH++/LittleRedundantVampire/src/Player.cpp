#include "Player.h"


Player::Player(Texture* texture, Vector2u imageCount, float switchTime, float speed) :
	//Her opretter vi en animation med de parametre som er g�ldende for Player.
	animation(texture, imageCount, switchTime),
	attack("AttackSheet2.png")
{
	this->speed = speed;

	row = 0;
	attackTimer = 0.0f;
	attackLength = 0.1f;

	faceRight = true;
	moving = false;
	drawAttack = false;
	canMove = true;

	//Definer st�rrelsen af �n sprite fra sheet.
	body.setSize(Vector2f(texture->getSize().x / 4, texture->getSize().y / 3));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(100.0f, 100.0f);
	//Vi s�tter player-variablens til at have vores texture.
	body.setTexture(texture);

	attack.SetPosition(Vector2f(body.getPosition().x, body.getPosition().y + 75.0f));
	attack.SetRow(1);
}

Player::~Player()
{
}


void Player::Update(float deltaTime)
{
	attackTimer += deltaTime;

	//Bestemmer hvilken retning du bev�ger dig.
	Vector2f movement(0.0f, 0.0f);


	//Bestemmer hvilken retning du skal �ndre til baseret p� input fra keyboard.
	//Venstre
	if (Keyboard::isKeyPressed(Keyboard::A) && canMove)
	{
		movement.x -= deltaTime;

		if (attackTimer >= attackLength)
		{
			attack.SetPosition(Vector2f(body.getPosition().x - 60.0f, body.getPosition().y));
			attack.SetColumn(1);
		}
	}
	//Højre
	else if (Keyboard::isKeyPressed(Keyboard::D) && canMove)
	{
		movement.x += deltaTime;

		if (attackTimer >= attackLength)
		{
			attack.SetPosition(Vector2f(body.getPosition().x + 60.0f, body.getPosition().y));
			attack.SetColumn(0);
		}
	}
	//Op
	else if (Keyboard::isKeyPressed(Keyboard::W) && canMove)
	{
		movement.y -= deltaTime;

		if (attackTimer >= attackLength)
		{
			attack.SetPosition(Vector2f(body.getPosition().x, body.getPosition().y - 70.0f));
			attack.SetColumn(2);
		}
	}
	//Ned
	else if (Keyboard::isKeyPressed(Keyboard::S) && canMove)
	{
		movement.y += deltaTime;

		if (attackTimer >= attackLength)
		{
			attack.SetPosition(Vector2f(body.getPosition().x, body.getPosition().y + 70.0f));
			attack.SetColumn(3);
		}
	}


	//Her angriber spilleren.
	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		drawAttack = true;
		attackTimer = 0.0f;
		canMove = false;
	}
	else if (attackTimer >= attackLength)
	{
		drawAttack = false;
		canMove = true;
	}


	//Her indstiller man idle animation n�r du st�r stille.
	if (movement.x == 0.0f && movement.y == 0.0f)
		//Bruges til at s�rge for, at den rigtige sprite tegnes n�r vi st�r stille.
		moving = false;
	//Start en walk cycle.
	else
	{
		//Vi udregner hypotenusen af bev�gelsesretningen.
		float movementVectorLength = sqrt(movement.x * movement.x + movement.y * movement.y);

		//Vi normaliserer retningen ift til hypotenusens l�ngde.
		Normalize(movement);

		moving = true;

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
			row = 0;
		//Op
		else if (movement.y < 0.0f)
			row = 2;
	}


	//Vi kan nu opdatere og tegne.
	animation.Update(row, deltaTime, faceRight, moving);
	body.setTextureRect(animation.TextureRect);
	body.move(movement);
	attack.Update(deltaTime);
}

void Player::Draw(RenderWindow& window)
{
	window.draw(body);

	if (drawAttack)
		attack.Draw(window);

}

void Player::Normalize(Vector2f& movement)
{
	//Vi udregner hypotenusen af bev�gelsesretningen.
	float movementVectorLength = sqrt(movement.x * movement.x + movement.y * movement.y);

	//Vi normaliserer retningen ift til hypotenusens l�ngde.
	movement.x /= movementVectorLength;
	movement.y /= movementVectorLength;

	movement.x *= speed;
	movement.y *= speed;
}
