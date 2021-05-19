#pragma once

#ifndef  STATE_H
#define STATE_H

#include "../GameObject.h"

class ContextState;
class Enemy;

class IState
{
protected:
	ContextState* context;

public:
	IState() {};
	~IState() {};

	// TODO: Can be deleted? I'm not sure why...
	//void SetContext(ContextState* context)
	//{
	//	this->context = context;
	//}

	/// <summary>
	/// Initial setup that needs to be done before the state can run.
	/// Enemy is set here, so the state knows which enemy it's working with.
	/// </summary>
	/// <param name="enemy"> The enemy the state is working with. </param>
	virtual void Enter(Enemy* enemy) = 0;

	/// <summary>
	/// Runs the actual code for the state. What happens during this state is run here.
	/// </summary>
	virtual void Execute() = 0;

	/// <summary>
	/// A place to delete all variables and pointers etc. We also change the state here.
	/// </summary>
	virtual void Exit() = 0;
};

#endif // ! STATE_H