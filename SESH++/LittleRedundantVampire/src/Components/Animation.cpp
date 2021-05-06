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
	TextureRect.width = texture->getSize().x / float(imageCount.x);
	TextureRect.height = texture->getSize().y / float(imageCount.y);
}

Animation::~Animation()
{
}

void Animation::Update(int row, float deltaTime, bool faceRight, bool moving)
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

		//Når vi ikke bevæger os, skal der altid bare hvis den første sprite i vores række.
		if (!moving)
		{
			currentImage.x = 0;
		}
		//Hvis vi bevæger os, skal den cycle igennem kolonnen.
		else if (moving)
		{
			//Sørger for at næste cycle skifter til det næste billede i rækken.
			currentImage.x++;

			//Her sørger vi for, at vi ikke overstiger den egentlige mængde af billeder i rækken.
			if (currentImage.x >= imageCount.x)
			{
				currentImage.x = 0;
			}
		}
	}

	//Vi udregner hvor toppen på vores sprite ligger, baseret på y-aksen (rækken) og sprite-højden.
	//F.eks. (top = 0 * 20 = 0).
	TextureRect.top = currentImage.y * TextureRect.height;

	//Hvordan vi definerer venstre side og spillerens bredde, hvis vi vender mod højre
	//Standard-retningen.
	if (faceRight)
	{
		//Vi udregner hvor venstre side vores sprite ligger, baseret på x-aksen (kolonnen) og sprite-bredden.
		//F.eks. (left = 1 * 20 = 20).
		TextureRect.left = currentImage.x * TextureRect.width;
		//Standard bredden er altid lige med den normale bredde.
		TextureRect.width = abs(TextureRect.width);
	}
	//Her flipper vi spriten når spilleren vender mod venstre.
	else
	{
		//Vi udregner hvor venstre side vores sprite ligger, baseret på x-aksen (kolonnen) og sprite-bredden.
		//Ved at lægge 1 til x-aksen, kan vi forskyde hvor den venstre side ligger, og således flip den.
		//F.eks. (left = 1 * 20 = 20).
		TextureRect.left = (currentImage.x + 1) * abs(TextureRect.width);
		//Her skal bredden være den negative version af standard-bredden, for at vi kan flippe vores sprite.
		TextureRect.width = -abs(TextureRect.width);
	}
}