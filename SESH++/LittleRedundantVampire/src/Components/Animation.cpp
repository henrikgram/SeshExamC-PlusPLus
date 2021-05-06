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
	TextureRect.width = texture->getSize().x / float(imageCount.x);
	TextureRect.height = texture->getSize().y / float(imageCount.y);
}

Animation::~Animation()
{
}

void Animation::Update(int row, float deltaTime, bool faceRight, bool moving)
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

		//N�r vi ikke bev�ger os, skal der altid bare hvis den f�rste sprite i vores r�kke.
		if (!moving)
		{
			currentImage.x = 0;
		}
		//Hvis vi bev�ger os, skal den cycle igennem kolonnen.
		else if (moving)
		{
			//S�rger for at n�ste cycle skifter til det n�ste billede i r�kken.
			currentImage.x++;

			//Her s�rger vi for, at vi ikke overstiger den egentlige m�ngde af billeder i r�kken.
			if (currentImage.x >= imageCount.x)
			{
				currentImage.x = 0;
			}
		}
	}

	//Vi udregner hvor toppen p� vores sprite ligger, baseret p� y-aksen (r�kken) og sprite-h�jden.
	//F.eks. (top = 0 * 20 = 0).
	TextureRect.top = currentImage.y * TextureRect.height;

	//Hvordan vi definerer venstre side og spillerens bredde, hvis vi vender mod h�jre
	//Standard-retningen.
	if (faceRight)
	{
		//Vi udregner hvor venstre side vores sprite ligger, baseret p� x-aksen (kolonnen) og sprite-bredden.
		//F.eks. (left = 1 * 20 = 20).
		TextureRect.left = currentImage.x * TextureRect.width;
		//Standard bredden er altid lige med den normale bredde.
		TextureRect.width = abs(TextureRect.width);
	}
	//Her flipper vi spriten n�r spilleren vender mod venstre.
	else
	{
		//Vi udregner hvor venstre side vores sprite ligger, baseret p� x-aksen (kolonnen) og sprite-bredden.
		//Ved at l�gge 1 til x-aksen, kan vi forskyde hvor den venstre side ligger, og s�ledes flip den.
		//F.eks. (left = 1 * 20 = 20).
		TextureRect.left = (currentImage.x + 1) * abs(TextureRect.width);
		//Her skal bredden v�re den negative version af standard-bredden, for at vi kan flippe vores sprite.
		TextureRect.width = -abs(TextureRect.width);
	}
}