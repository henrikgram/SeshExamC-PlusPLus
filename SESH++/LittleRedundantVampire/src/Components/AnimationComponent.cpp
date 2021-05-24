#include "AnimationComponent.h"


AnimationComponent::AnimationComponent(SpriteRenderer* spriteRenderer, Vector2u imageCount, float switchTime, int row)
{
	textureRect = new IntRect;

	this->spriteRenderer = spriteRenderer;
	this->imageCount = imageCount;
	this->switchTime = switchTime;

	this->row = row;

	totalTime = 0.0f;

	//Which image to start animating from.
	currentImage.x = 0;

	//Defines size of the texture rectangle according to the spritesheet images.
	textureRect->width = spriteRenderer->GetTexture().getSize().x / float(imageCount.x);
	textureRect->height = spriteRenderer->GetTexture().getSize().y / float(imageCount.y);
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
	//Which row to cycle through.
	currentImage.y = row;
	//We define our totalTime according to the time that's passed since last update.
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

	//Find the left and top position of the current image in the spritesheet animation.
	//This way we can know which image is the correct one.
	textureRect->left = currentImage.x * textureRect->width;
	textureRect->top = currentImage.y * textureRect->height;
	textureRect->width = abs(textureRect->width);

	spriteRenderer->SetTextureRect(*textureRect);
}

void AnimationComponent::Destroy()
{

}

void AnimationComponent::OnNotify(string eventName, IListener* sender)
{
	//For flipping the sprite when facing left.
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
