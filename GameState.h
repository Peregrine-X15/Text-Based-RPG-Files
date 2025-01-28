#pragma once
#include "I_state.h"
#include "../selector.h"
#include "../Player.h"
#include <memory>
#include "../Party.h"
#include "../Inventory.h"
#include "../Stats.h"
#include "../utilities/Timer.h"
class Console;
class Keyboard;
class StateMachine;

class GameState : public IState
{
private:
	Console& m_Console;
	Keyboard& m_keyboard;
	StateMachine& m_StateMachine;

	Selector<> m_Selector;
	std::unique_ptr<Party> m_Party;
	//std::unique_ptr<Player> m_TestPlayer;
	Timer m_Timer;
	Inventory m_TestInventory;
public:
	GameState(Console& console, Keyboard& keyboard,StateMachine& stateMachine);
	~GameState();

void OnEnter() override;
void OnExit() override;
void Update() override;
void Draw() override;
void ProcessInputs() override;
bool Exit() override;
};