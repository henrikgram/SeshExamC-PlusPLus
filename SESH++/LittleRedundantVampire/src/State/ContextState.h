#pragma once
#include "IState.h"

#ifndef  CONTEXTSTATE_H
#define CONTEXTSTATE_H

class Enemy;
class ContextState
{
private:
	IState* state;

public:
	ContextState(IState* state);
	~ContextState();

	void TransitionTo(IState* nextState);
	void StartRequest(Enemy* enemy);
	void ExitRequest();
};

#endif