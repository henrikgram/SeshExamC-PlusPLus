#include "Animation.h"


Animation::Animation(Texture* texture, Vector2u imageCount, float switchTime)
{
	//Vi definerer imageCount og switchTime fra header.
	this->imageCount = imageCount;
	this->switchTime = switchTime;

	totalTime = 0.0f;
	//Hvilket image skal vi starte animationen fra i vores r�kke.
	currentImage.x = 0;

	//Vi skal definere bredden og h�jden p� vores textureRectangle ift til png-filen, s� sprite for den rigtige dimension.
	textureRect.width = texture->getSize().x / float(imageCount.x);
	textureRect.height = texture->getSize().y / float(imageCount.y);
}

Animation::~Animation()
{
}

void Animation::Update(int row, float deltaTime, bool faceRight)
{
	//Vi definerer hvilken r�kke og kolonne der skal cycles igennem.
	currentImage.y = row;
	//Vi definerer vores totalTime ift. den tid der er g�et siden sidste update.
	totalTime += deltaTime;

	//N�r totalTime overstiger vores switchTime, s� er det tid til at skifte til n�ste billede.
	if (totalTime >= switchTime)
	{
		//I stedet for at s�tter totalTime=0 g�r vi s�ledes, da det giver en mere smooth animation.
		totalTime -= switchTime;
		//S�rger for at n�ste cycle skifter til det n�ste billede i r�kken.
		currentImage.x++;

		//Her s�rger vi for, at vi ikke overstiger den egentlige m�ngde af billeder i r�kken.
		if (currentImage.x >= imageCount.x)
		{
			currentImage.x = 0;
		}
	}

	textureRect.top = currentImage.y * textureRect.height;

	if (faceRight)
	{
		//Det her fatter jeg sgu ikke 100%.
		textureRect.left = currentImage.x * textureRect.width;
		textureRect.width = abs(textureRect.width);
	}
	else
	{
		//Det her fatter jeg sgu ikke 100%.
		textureRect.left = (currentImage.x + 1) * abs(textureRect.width);
		textureRect.width = -abs(textureRect.width);
	}
}
