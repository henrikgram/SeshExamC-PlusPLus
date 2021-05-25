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
	delete currentRow;
	currentRow = nullptr;
}


void AnimationController::MovementAnimation()
{
	//TODO: OPTIMERING fix s� den ikke k�rer medmindre det er en ny animation. OPTIMERING
	//No/idle animation
	if (*gameObject->GetDirection() == 'N')
	{
		ChangeAnimation.Notify(noAniRow, this);
	}

	//Up
	else if (*gameObject->GetDirection() == 'U')
	{
		ChangeAnimation.Notify(upAniRow, this);
	}

	//Down
	else if (*gameObject->GetDirection() == 'D')
	{
		ChangeAnimation.Notify(downAniRow, this);
	}

	//Left
	else if (*gameObject->GetDirection() == 'L')
	{
		if (!*spriteRenderer.GetFlipped())
		{
			*spriteRenderer.GetFlipped() = true;
			ChangeAnimation.Notify("flip", this);
		}

		ChangeAnimation.Notify(leftAniRow, this);
	}

	//Right
	else if (*gameObject->GetDirection() == 'R')
	{
		if (*spriteRenderer.GetFlipped())
		{
			*spriteRenderer.GetFlipped() = false;
			ChangeAnimation.Notify("flip", this);
		}

		ChangeAnimation.Notify(rightAniRow, this);
	}
}

void AnimationController::DecrementingRowAnimation()
{
	//If the currentRow has changed from the previous, update the animation.
	if (previousRow != *currentRow)
	{
		string newRow = to_string(firstRow - *currentRow);
		ChangeAnimation.Notify(newRow, this);

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
