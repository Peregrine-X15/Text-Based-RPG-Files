#include "StateMachine.h"

StateMachine::StateMachine()
	:m_states()
{
}

StateMachine::~StateMachine()
{
}

void StateMachine::PushState(StatePtr newState)
{
	m_states.push(std::move(newState));
	m_states.top()->OnEnter();
}

StatePtr StateMachine::PopState()
{
	if(m_states.empty())
	return nullptr;

	auto oldState = std::move(m_states.top());

	m_states.pop();

	oldState->OnExit();

	return oldState;
}

StatePtr& StateMachine::GetCurrentState()
{
	return m_states.top();
	// TODO: insert return statement here
}
