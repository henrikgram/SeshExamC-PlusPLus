#include "../Headers/Components/OldPlayer.h"

OldPlayer::OldPlayer(Texture* texture, Vector2u imageCount, float switchTime, float speed) :
	//Her opretter vi en animation med de parametre som er gaeldende for Player.
	animation(texture, imageCount, switchTime),
	attack("Asset/AttackSheet2.png")
{
	this->speed = speed;

	row = 0;
	attackTimer = 0.0f;
	attackLength = 0.1f;

	faceRight = true;
	moving = false;
	drawAttack = false;
	canMove = true;

	//Definer storrelsen af en sprite fra sheet.
	body.setSize(Vector2f(texture->getSize().x / 4, texture->getSize().y / 3));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(100.0f, 100.0f);
	//Vi saetter player-variablens til at have vores texture.
	body.setTexture(texture);

	attack.SetPosition(Vector2f(body.getPosition().x, body.getPosition().y + 75.0f));
	attack.SetRow(1);
}

OldPlayer::~OldPlayer()
{
}


void OldPlayer::Update(float deltaTime)
{
	attackTimer += deltaTime;

	//Bestemmer hvilken retning du bevaeger dig.
	Vector2f movement(0.0f, 0.0f);


	//Bestemmer hvilken retning du skal aendre til baseret paa input fra keyboard.
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
	//Hoejre
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


	//Her indstiller man idle animation naar du staar stille.
	if (movement.x == 0.0f && movement.y == 0.0f)
		//Bruges til at soerge for, at den rigtige sprite tegnes naar vi staar stille.
		moving = false;
	//Start en walk cycle.
	else
	{
		//Vi udregner hypotenusen af bevaegelsesretningen.
		float movementVectorLength = sqrt(movement.x * movement.x + movement.y * movement.y);

		//Vi normaliserer retningen ift til hypotenusens laengde.
		Normalize(movement);

		moving = true;

		//Hoejre
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

void OldPlayer::Draw(RenderWindow& window)
{
	window.draw(body);

	if (drawAttack)
		attack.Draw(window);

}

void OldPlayer::Normalize(Vector2f& movement)
{
	//Vi udregner hypotenusen af bevaegelsesretningen.
	float movementVectorLength = sqrt(movement.x * movement.x + movement.y * movement.y);

	//Vi normaliserer retningen ift til hypotenusens laengde.
	movement.x /= movementVectorLength;
	movement.y /= movementVectorLength;

	movement.x *= speed;
	movement.y *= speed;
}
