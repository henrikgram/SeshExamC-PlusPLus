﻿#include "AnimationController.h"


AnimationController::AnimationController(SpriteRenderer& spriteRenderer,
	string noAniRow, string upAniRow, string downAniRow, string leftAniRow, string rightAniRow)
	:
	spriteRenderer(spriteRenderer)
{
	this->noAniRow = noAniRow;
	this->upAniRow = upAniRow;
	this->downAniRow = downAniRow;
	this->leftAniRow = leftAniRow;
	this->rightAniRow = rightAniRow;

	isMovable = true;
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

	//No/Idle animation
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

void AnimationController::Awake()
{
}

void AnimationController::Start()
{
}

void AnimationController::Update(Time* timePerFrame)
{
	if (isMovable)
	{
		MovementAnimation();
	}
}

void AnimationController::Destroy()
{
}

ComponentTag AnimationController::ToEnum()
{
	return ComponentTag::ANIMATION_CONTROLLER;
}
