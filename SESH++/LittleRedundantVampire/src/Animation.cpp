#include "Animation.h"


Animation::Animation(Texture* texture, Vector2u imageCount, float switchTime)
{
	//Vi definerer imageCount og switchTime fra header.
	this->imageCount = imageCount;
	this->switchTime = switchTime;

	totalTime = 0.0f;
	//Hvilket image skal vi starte animationen fra i vores række.
	currentImage.x = 0;

	//Vi skal definere bredden og højden på vores textureRectangle ift til png-filen, så sprite for den rigtige dimension.
	textureRect.width = texture->getSize().x / float(imageCount.x);
	textureRect.height = texture->getSize().y / float(imageCount.y);
}

Animation::~Animation()
{
}

void Animation::Update(int row, float deltaTime, bool faceRight)
{
	//Vi definerer hvilken række og kolonne der skal cycles igennem.
	currentImage.y = row;
	//Vi definerer vores totalTime ift. den tid der er gået siden sidste update.
	totalTime += deltaTime;

	//Når totalTime overstiger vores switchTime, så er det tid til at skifte til næste billede.
	if (totalTime >= switchTime)
	{
		//I stedet for at sætter totalTime=0 gør vi således, da det giver en mere smooth animation.
		totalTime -= switchTime;
		//Sørger for at næste cycle skifter til det næste billede i rækken.
		currentImage.x++;

		//Her sørger vi for, at vi ikke overstiger den egentlige mængde af billeder i rækken.
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
