#include "AnimationController.h"


AnimationController::AnimationController(SpriteRenderer& spriteRenderer, string noAniRow, string upAniRow,
										 string downAniRow, string leftAniRow, string rightAniRow) : spriteRenderer(spriteRenderer)
{
	this->noAniRow = noAniRow;
	this->upAniRow = upAniRow;
	this->downAniRow = downAniRow;
	this->leftAniRow = leftAniRow;
	this->rightAniRow = rightAniRow;

	movementAnimation = true;
	decrementAnimation = false;
}

AnimationController::AnimationController(SpriteRenderer& spriteRenderer, int* currentRow, int firstRow) : spriteRenderer(spriteRenderer)
{
	this->currentRow = currentRow;
	previousRow = *this->currentRow;
	this->firstRow = firstRow;

	movementAnimation = false;
	decrementAnimation = true;
}

AnimationController::~AnimationController()
{

}


void AnimationController::MovementAnimation()
{
	//TODO:* OPTIMIZE Make it so this doesn't run notify unless there's a new animation update.


	//No/idle animation
	if (*gameObject->GetDirection() == 'N')
	{
		changeAnimation.Notify(noAniRow, this);
	}

	//Up
	else if (*gameObject->GetDirection() == 'U')
	{
		changeAnimation.Notify(upAniRow, this);
	}

	//Down
	else if (*gameObject->GetDirection() == 'D')
	{
		changeAnimation.Notify(downAniRow, this);
	}

	//Left
	else if (*gameObject->GetDirection() == 'L')
	{
		if (!*spriteRenderer.GetFlipped())
		{
			*spriteRenderer.GetFlipped() = true;
			changeAnimation.Notify("flip", this);
		}

		changeAnimation.Notify(leftAniRow, this);
	}

	//Right
	else if (*gameObject->GetDirection() == 'R')
	{
		if (*spriteRenderer.GetFlipped())
		{
			*spriteRenderer.GetFlipped() = false;
			changeAnimation.Notify("flip", this);
		}

		changeAnimation.Notify(rightAniRow, this);
	}
}

void AnimationController::DecrementingRowAnimation()
{
	//If the currentRow has changed from the previous, update the animation.
	if (previousRow != *currentRow)
	{
		string newRow = to_string(firstRow - *currentRow);
		changeAnimation.Notify(newRow, this);

		previousRow = *currentRow;
	}
}

void AnimationController::Awake()
{
}

void AnimationController::Start()
{
}

void AnimationController::Update(Time* timePerFrame)
{
	if (movementAnimation)
	{
		MovementAnimation();
	}
	else if (decrementAnimation)
	{
		DecrementingRowAnimation();
	}
}

void AnimationController::Destroy()
{
	AnimationController::~AnimationController();
}

ComponentTag AnimationController::ToEnum()
{
	return ComponentTag::ANIMATION_CONTROLLER;
}

void AnimationController::AttachListenerToChangeAnimation(IListener* listener)
{
	changeAnimation.Attach(listener);
}
