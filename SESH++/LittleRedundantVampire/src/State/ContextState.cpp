#include "ContextState.h"

ContextState::ContextState(IState* state) : state(nullptr)
{
	this->TransitionTo(state);
}

ContextState::~ContextState()
{
	//delete state;
}

void ContextState::TransitionTo(IState* nextState)
{
	state = nextState;
}

void ContextState::StartRequest(Enemy* enemy)
{
	state->Enter(enemy);
}

void ContextState::RunRequest()
{
	state->Execute();
}