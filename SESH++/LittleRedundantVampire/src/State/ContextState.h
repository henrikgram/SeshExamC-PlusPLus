#ifndef  CONTEXTSTATE_H
#define CONTEXTSTATE_H

#include "IState.h"


class Enemy;
class ContextState
{
private:
	IState* state;

public:
	ContextState(IState* state);
	~ContextState();

	/// <summary>
	/// Changes the state to a new state.
	/// </summary>
	/// <param name="nextState"> The new state that enemy needs to change to </param>
	void TransitionTo(IState* nextState);
	/// <summary>
	/// We run all Enter() methods from here.
	/// Initial code that needs to run before the "real" state code can start.
	/// </summary>
	/// <param name="enemy"></param>
	void StartRequest(Enemy* enemy);
	/// <summary>
	/// All Execute() methods are run from here.
	/// What actually happens in each state is run in the state's Execute() method.
	/// </summary>
	void RunRequest();
};

#endif