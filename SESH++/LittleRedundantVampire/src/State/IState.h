#pragma once
#include "../GameObject.h"

#ifndef  STATE_H
#define STATE_H

class ContextState;
class Enemy;
class IState
{
protected:
	ContextState* context;

public:
	IState() {};
	~IState() {};

	void SetContext(ContextState* context)
	{
		this->context = context;
	}

	virtual void Enter(Enemy* enemy) = 0;
	virtual void Execute() = 0;
	virtual void Exit() = 0;
};

#endif // ! STATE_H