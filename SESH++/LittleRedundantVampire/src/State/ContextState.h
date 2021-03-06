#ifndef  CONTEXTSTATE_H
#define CONTEXTSTATE_H

#include "IState.h"


class Enemy;
class ContextState
{
private:
	IState* state;

public:
	/// <summary>
	/// Constructor for ContextState. State is the state the object starts in.
	/// Fx. in this case either idle- or chase-state.
	/// </summary>
	/// <param name="state"> The state the object starts in </param>
	ContextState(IState* state);
	~ContextState();

	/// <summary>
	/// Changes the state to a new state.
	/// </summary>
	/// <param name="nextState"> The new state that enemy needs to change to </param>
	void TransitionTo(IState* nextState);
	/// <summary>
	/// All Enter() methods run from here.
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