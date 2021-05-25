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
	//TODO: man behøver vist ikke at slette her, fordi det ikke er på heap.
	/*if (this->state != nullptr)
	{
		delete this->state;
	}*/

	this->state = nextState;
	// TODO: Can be deleted? The below code.. don't get it but ok.
	//this->state->IState::SetContext(this);
}

void ContextState::StartRequest(Enemy* enemy)
{
	this->state->Enter(enemy);
}

void ContextState::RunRequest()
{
	this->state->Execute();
}