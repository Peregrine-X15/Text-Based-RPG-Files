#include "GameMenuState.h"
#include "../Party.h"
#include "../Player.h"
#include "../Console.h"
#include "../inputs/Keyboard.h"
#include "StateMachine.h"

using namespace std::placeholders;
void GameMenuState::DrawPanels()
{
}

void GameMenuState::DrawPlayerInfo()
{
	for (int i = 1; const auto & player: m_Party.GetParty())
	{
		if (!player->IsActive())
			continue;
		
		const auto& name = player->GetName();
		const auto& hp = std::to_wstring(player->GetHP());
		const auto& hp_max = std::to_wstring(player->GetMaxHP());
		const auto& level = std::to_wstring(player->GetLevel());
		const auto& xp = std::to_wstring(player->GetXP());
		const auto& xp_to_next = std::to_wstring(player->GetXPToNextLevel());

		std::wstring hp_string = L"HP: " + hp + L" / " + hp_max;
		std::wstring level_string = L"Lvl: " + level + L"Exp: " + xp + L" / " + xp_to_next;

		m_Console.Write(75, 12 + i, name, LIGHT_AQUA);
		m_Console.Write(75, 13 + i, hp_string, LIGHT_AQUA);
		m_Console.Write(75, 14 + i, level_string, LIGHT_AQUA);
		i += 10;
	}
	// draw the party gold
	const auto& gold = std::to_wstring(m_Party.GetGold());

	std::wstring gold_str = L"Credits: " + gold;
	m_Console.Write(26, 36, gold_str);
}

void GameMenuState::OnMenuSelect(int index, std::vector<std::wstring> data)
{
	switch (index)
	{
	case 0:
		m_eSelectType = SelectType::ITEM;
		break;
	case 1:
		m_eSelectType = SelectType::MAGIC;
		break;
	case 2:
		m_eSelectType = SelectType::EQUIPMENT;
		break;
	case 3:
		m_eSelectType = SelectType::STATS;
		break;
	case 4:
		m_eSelectType = SelectType::ORDER;
		break;
	case 5:
		//SAVE GAME TO DO
		return;
	case 6:
		m_bExitGame=true;
		return;
	default:
		return;
	}
	if (m_eSelectType != SelectType::NONE)
	{
		m_MenuSelector.HideCursor();
		m_PlayerSelector.ShowCursor();
		m_bInMenuSelect = false;
	}
}

void GameMenuState::OnPlayerSelect(int index, std::vector<std::shared_ptr<Player>> data)
{
	const auto& player = data[index];
	switch (m_eSelectType)
	{
	case SelectType::ITEM:
		//to do: create new item state
		break;
	case SelectType::MAGIC:
		//create a magic state to do
		break;
	case SelectType::EQUIPMENT:
		//to do create equipment state
		break;
	case SelectType::STATS:
		//to do create stats state
		break;
	case SelectType:: ORDER:
		// to do create order state
		break;
	default: 
		break;
	}
}

void GameMenuState::OnDrawPlayerSelect(int x, int y, std::shared_ptr<Player> player)
{
	/*nothing to do here just placeholder*/
}

GameMenuState::GameMenuState(Party& party, Console& console, StateMachine& stateMachine, Keyboard& keyboard)
	: m_Party(party)
	,m_Console(console)
	,m_StateMachine(stateMachine)
	,m_Keyboard(keyboard)
	, m_MenuSelector{
		console,
		keyboard,
		{L"Items", L"Abilities", L"Equipment",L"Stats", L"Order", L"Save", L"Exit"},
	SelectorParams{30, 8,1,0,4} }
	, m_PlayerSelector{
			console,
			keyboard,
			std::bind(&GameMenuState::OnPlayerSelect, this, _1,_2),
			std::bind(&GameMenuState::OnDrawPlayerSelect, this, _1,_2,_3),
			party.GetParty(),
			SelectorParams{69, 13 ,1, 0,10} }	
			, m_bExitGame{false}, m_bInMenuSelect{true}
	,m_ScreenWidth{console.GetScreenWidth()}
	, m_ScreenHeight{ console.GetScreenHeight() }
	, m_CenterScreenW{console.GetHalfWidth()}, m_PanelBarX{m_CenterScreenW-(PANEL_BARS/2)}
	, m_eSelectType{SelectType::NONE}
{
	m_MenuSelector.SetSelectionFunc(std::bind(&GameMenuState::OnMenuSelect, this, _1, _2));
}

GameMenuState::~GameMenuState()
{
}

void GameMenuState::OnEnter()
{
	if (m_bInMenuSelect)
		m_PlayerSelector.HideCursor();

	m_Console.ClearBuffer();
}

void GameMenuState::OnExit()
{
	m_Console.ClearBuffer();
}

void GameMenuState::Update()
{
}

void GameMenuState::Draw()
{
	//m_Console.Write(20, 10, L"We are in the game menu", BLUE);
	DrawPanels();
	DrawPlayerInfo();

	m_MenuSelector.Draw();
	m_PlayerSelector.Draw();

	m_Console.Draw();
}

void GameMenuState::ProcessInputs()
{
	if (m_bInMenuSelect)
	{
		if (m_Keyboard.IsKeyJustPressed(KEY_BACKSPACE))
		{
			m_StateMachine.PopState();
			return;
		}
		m_MenuSelector.ProcessInputs();
	}
	else
	{
		if (m_Keyboard.IsKeyJustPressed(KEY_BACKSPACE))
		{
			m_StateMachine.PopState();
			m_bInMenuSelect = true;
			m_eSelectType = SelectType::NONE;
			m_MenuSelector.ShowCursor();
			m_Console.ClearBuffer();
			return;
		}
		m_PlayerSelector.ProcessInputs();
	}
}

bool GameMenuState::Exit()
{
	return m_bExitGame;
}
