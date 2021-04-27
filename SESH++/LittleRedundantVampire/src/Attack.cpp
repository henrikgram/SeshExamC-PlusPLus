#include "Attack.h"


Attack::Attack(Texture* texture, Vector2f spawnPosition, float attackTime)
{
	faceRight = true;
	faceUp = false;

	//Definer st�rrelsen af �n sprite fra sheet.
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(spawnPosition);
	//Vi s�tter player-variablens til at have vores texture.
	body.setTexture(texture);
}

Attack::~Attack()
{
}


void Attack::Update(float deltaTime)
{
	
}

void Attack::Draw(RenderWindow& window)
{
	window.draw(body);
}

