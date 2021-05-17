#pragma once
#include "IState.h"

class ContextState
{
private:
	IState* state;

public:
	ContextState(IState* state);
	~ContextState();

	void TransitionTo(IState* nextState);
	void StartRequest();
	void ExitRequest();
};

