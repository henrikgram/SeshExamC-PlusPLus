#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(SpriteRenderer* spriteRenderer, Vector2u imageCount, float switchTime, int row)
{
	TextureRect = new IntRect;
	this->spriteRenderer = spriteRenderer;
	//Vi definerer imageCount og switchTime fra header.
	this->imageCount = imageCount;
	this->switchTime = switchTime;

	this->row = row;

	totalTime = 0.0f;
	//Hvilket image skal vi starte animationen fra i vores r�kke.
	currentImage.x = 0;

	//Vi skal definere bredden og h�jden p� vores textureRectangle ift til png-filen, s� sprite for den rigtige dimension.
	TextureRect->width = spriteRenderer->GetTexture().getSize().x / float(imageCount.x);
	TextureRect->height = spriteRenderer->GetTexture().getSize().y / float(imageCount.y);
}

AnimationComponent::~AnimationComponent()
{
}


void AnimationComponent::Awake()
{
}

void AnimationComponent::Start()
{
}

void AnimationComponent::Update(Time* timePerFrame)
{
	//Vi definerer hvilken r�kke og kolonne der skal cycles igennem.
	currentImage.y = row;
	//Vi definerer vores totalTime ift. den tid der er g�et siden sidste update.
	totalTime += timePerFrame->asMilliseconds();

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.x++;

		if (currentImage.x >= imageCount.x)
		{
			currentImage.x = 0;
		}
	}

	TextureRect->left = currentImage.x * TextureRect->width;
	TextureRect->top = currentImage.y * TextureRect->height;
	TextureRect->width = abs(TextureRect->width);

	//spriteRenderer->sprite->setTextureRect(*TextureRect);
	spriteRenderer->SetTextureRect(*TextureRect);
}

void AnimationComponent::Destroy()
{

}

void AnimationComponent::OnNotify(string eventName, IListener* sender)
{

	//convert string to int
	//If it fails the conversion it checks for other augments
	//TODO: tjek om det er cursed at s� voldsomt udnytte en trycatch
	//TODO: det var det
	if (eventName != "NoLongerCollidingWith")
	{
		if (eventName == "flip")
		{
			spriteRenderer->FlipSprite();
		}
		else
		{
			//convert string to int
			row = stoi(eventName);
		}
	}
}



ComponentTag AnimationComponent::ToEnum()
{
	return ComponentTag::ANIMATION;
}
