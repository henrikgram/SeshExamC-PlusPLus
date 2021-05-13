#include "AnimationController.h"


AnimationController::AnimationController(Movement* movementComponent, SpriteRenderer* spriteRenderer, GameObject* gameObject,
	string noAniRow, string upAniRow, string downAniRow, string leftAniRow, string rightAniRow)
{
	this->movementComponent = movementComponent;
	this->spriteRenderer = spriteRenderer;
	this->gameObject = gameObject;

	this->noAniRow = noAniRow;
	this->upAniRow = upAniRow;
	this->downAniRow = downAniRow;
	this->leftAniRow = leftAniRow;
	this->rightAniRow = rightAniRow;
}

AnimationController::~AnimationController()
{
}

/// <summary>
/// For animating objects that move in four directions, like the Player.
/// </summary>
void AnimationController::MovementAnimation()
{
	//TODO: OPTIMERING fix s� den ikke k�rer medmindre det er en ny animation. OPTIMERING
	if ((*movementComponent->GetVelocity()).x == 0 && (*movementComponent->GetVelocity()).y == 0)
	{
		if (*gameObject->GetDirection() != 'N')
		{
			ChangeAnimation.Notify(noAniRow, this);
			*gameObject->GetDirection() = 'N';
		}
	}

	else if ((*movementComponent->GetVelocity()).y < 0)
	{
		if (*gameObject->GetDirection() != 'U')
		{
			ChangeAnimation.Notify(upAniRow, this);
			*gameObject->GetDirection() = 'U';
		}
	}

	else if ((*movementComponent->GetVelocity()).y > 0)
	{
		if (*gameObject->GetDirection() != 'D')
		{
			ChangeAnimation.Notify(downAniRow, this);
			*gameObject->GetDirection() = 'D';
		}
	}

	else if ((*movementComponent->GetVelocity()).x < 0)
	{
		if (*gameObject->GetDirection() != 'L')
		{
			if (!*spriteRenderer->GetFlipped())
			{
				*spriteRenderer->GetFlipped() = true;
				ChangeAnimation.Notify("flip", this);
			}
			ChangeAnimation.Notify(leftAniRow, this);
			*gameObject->GetDirection() = 'L';
		}
	}

	else if ((*movementComponent->GetVelocity()).x > 0)
	{
		if (*gameObject->GetDirection() != 'R')
		{
			if (*spriteRenderer->GetFlipped())
			{
				*spriteRenderer->GetFlipped() = false;
				ChangeAnimation.Notify("flip", this);
			}
			ChangeAnimation.Notify(rightAniRow, this);
			*gameObject->GetDirection() = 'R';
		}
	}
}

void AnimationController::OnNotify(std::string eventName, IListener* sender)
{
}
