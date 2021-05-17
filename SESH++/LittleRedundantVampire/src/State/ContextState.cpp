#include "ContextState.h"

ContextState::ContextState(IState* state) : state(nullptr)
{
	this->TransitionTo(state);
}

ContextState::~ContextState()
{
	delete state;
}

void ContextState::TransitionTo(IState* nextState)
{
	if (this->state != nullptr)
	{
		delete this->state;
	}
	this->state = nextState;
	this->state->IState::SetContext(this);
}

void ContextState::StartRequest()
{
	this->state->Execute();
}

void ContextState::ExitRequest()
{
	this->state->Exit();
}



