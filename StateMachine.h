#pragma once
#include <memory>
#include <stack>
#include "I_state.h"

typedef std::unique_ptr<IState> StatePtr;

class StateMachine
{
private:
		std::stack<StatePtr> m_states;

public:
	StateMachine();
	~StateMachine();

	void PushState(StatePtr newState);
	StatePtr PopState();
	const bool Empty() const { return m_states.empty(); }
	StatePtr& GetCurrentState();
};