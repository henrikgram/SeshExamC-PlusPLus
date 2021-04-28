#include "Attack.h"


Attack::Attack(string textureName)
{
	texture.loadFromFile(textureName);

	faceRight = true;
	faceUp = false;

	this->row = row;
	this->column = column;

	//Definer størrelsen af én sprite fra sheet.
	body.setSize(Vector2f(texture.getSize().x / 3.0f, texture.getSize().y / 1.5f));
	body.setOrigin(body.getSize() / 2.0f);
	//Vi sætter player-variablens til at have vores texture.
	body.setTexture(&texture);

	textureRect.width = texture.getSize().x / 4.0f;
	textureRect.height = texture.getSize().y / 2.0f;
}

Attack::~Attack()
{
}


void Attack::Update(float deltaTime)
{
	//Vi udregner hvor toppen på vores sprite ligger, baseret på y-aksen (rækken) og sprite-højden.
		//F.eks. (top = 0 * 20 = 0).
	textureRect.top = row * textureRect.height;

	//Vi udregner hvor venstre side vores sprite ligger, baseret på x-aksen (kolonnen) og sprite-bredden.
	//F.eks. (left = 1 * 20 = 20).
	textureRect.left = column * textureRect.width;
	//Standard bredden er altid lige med den normale bredde.
	textureRect.width = abs(textureRect.width);

	body.setTextureRect(textureRect);
}

void Attack::Draw(RenderWindow& window)
{
	window.draw(body);
}

