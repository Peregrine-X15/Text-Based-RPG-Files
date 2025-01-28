#include "GameState.h"
#include "StateMachine.h"
#include "../Logger.h"
#include "../inputs/Keyboard.h"
#include "../Console.h"
#include "../Stats.h"
#include "../Potion.h"
#include "../utilities/ItemCreator.h"
#include "GameMenuState.h"
GameState::GameState(Console& console, Keyboard& keyboard, StateMachine& stateMachine)
	: m_Console(console)
	,m_keyboard(keyboard)
	,m_StateMachine(stateMachine)
	, m_Selector(console, keyboard, {L"Start",L"Settings",L"Exit"})
	//, m_TestInventory{}
	,m_Party{nullptr}
	, m_Timer{}
{
	m_Party = std::make_unique<Party>();

	//create an item to add to inventory test
	auto potion = ItemCreator::CreateItem(Item::ItemType::HEALTH, L"Stimpack", L"Heals a for 25 HP and is worth 50 credits", 25, 50);
	m_Party->GetInventory().AddItem(std::move(potion));
	//create weapons here
	auto pistol = ItemCreator::CreateEquipment(Equipment::EquipType::WEAPON,
		WeaponProperties(15, WeaponProperties::WeaponType::PISTOL),
		ArmorProperties(),
		StatModifier(3,StatModifier::ModifierType::STRENGTH),
		L"MB1558",L"a basic handgun that fires 9mm ammo and is commonly used by the Central Galactic Armed Forces as a \
		sidearm or main weapon for officers. And is often seen in ceremonial usage.", 100,50
		);
	m_Party->GetInventory().AddEquipment(std::move(pistol));
	//create armor here
	auto chest_armor = ItemCreator::CreateEquipment(Equipment::EquipType::ARMOR,
		WeaponProperties(),
		ArmorProperties(10, ArmorProperties::ArmorType::CHEST_BODY),
		StatModifier(3, StatModifier::ModifierType::STRENGTH),
		L"Standard Issue Body Armor", L"Basic Central Galactic Armed Forces chest piece. Used to protect against \
standard firearms and weak energy weapons.", 100, 50
	);
	m_Party->GetInventory().AddEquipment(std::move(chest_armor));
	auto player = std::make_shared<Player>(L"Test Player", L"testPlayer", m_Party->GetInventory(), 1, 200);
	auto Kas = std::make_shared<Player>(L"Kas", L"marine", m_Party->GetInventory(), 1, 200);
	m_Party->AddMember(std::move(player));
	m_Party->AddMember(std::move(Kas));
}

GameState::~GameState()
{
}

void GameState::OnEnter()
{
	m_Console.ClearBuffer();
}

void GameState::OnExit()
{
	
	m_Console.ClearBuffer();
}

void GameState::Update()
{
	m_Console.ClearBuffer();
}

void GameState::Draw()
{
/*	for (const auto& member : m_Party->GetParty())
	{
		const auto& name = member->GetName();
		std::wstring hp = std::to_wstring(member->GetHP());
		std::wstring max_hp = std::to_wstring(member->GetMaxHP());

		m_Console.Write(50, 30, name, BLUE);
		m_Console.Write(50, 32, L"HP: " + hp + L"/" + max_hp, BLUE);

		const auto& stats_list = member->GetStats().GetStatList();
		int i = 0;
		for (const auto& [stat, value] : stats_list)
		{
			const auto& mod_value = member->GetStats().GetModifier(stat);
			m_Console.Write(50, 34 + i, stat + L":");
			m_Console.Write(70, 34 + i, std::to_wstring(value + mod_value));
			i++;
		}
	}
	*/
	std::wstring time_MS = L"MS: " + std::to_wstring(m_Timer.ElapsedMS());
	std::wstring time_SEC = L"SEC: " + std::to_wstring(m_Timer.ElapsedSec());

	m_Console.Write(25, 25, time_MS, BLUE);
	m_Console.Write(25, 26, time_SEC, YELLOWS);
	m_Selector.Draw();
	m_Console.Draw();
}

void GameState::ProcessInputs()
{
	if (m_keyboard.IsKeyJustPressed(KEY_ESCAPE))
	{
		m_StateMachine.PopState();
		return;
	}
	if (m_keyboard.IsKeyJustPressed(KEY_M))
	{
		m_StateMachine.PushState(std::make_unique<GameMenuState>(*m_Party, m_Console, m_StateMachine, m_keyboard));
		return;
	}
	if (m_keyboard.IsKeyJustPressed(KEY_ENTER))
	{
		m_Timer.Start();
	}
	else if (m_keyboard.IsKeyJustPressed(KEY_P))
	{
		m_Timer.Pause();
	}
	else if (m_keyboard.IsKeyJustPressed(KEY_R))
	{
		m_Timer.Resume();
	}
	else if (m_keyboard.IsKeyJustPressed(KEY_T))
	{
		m_Timer.Stop();
		m_Console.ClearBuffer();
	}
	m_Selector.ProcessInputs();
}

bool GameState::Exit()
{
	return false;
}
