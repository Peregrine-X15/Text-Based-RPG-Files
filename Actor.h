#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Stats.h"
#include <unordered_map>
#include "Equipment.h"
class Actor
{
public: 
	enum class ActorType
	{
		// marine: standard trooper, research officer: like mage, phoenix: thief/stealth, rhino: heavy, medic, SF: special forces high speed
		MARINE=0 , RSO, PHOENIX, RHINO, MEDIC, SF
	};
private:
	const std::vector<std::wstring>m_EquipmentSlotsLabels{ L"Weapon: ",L"Headgear: ", L"Armor: ",L"Footwear: ",L"Accessory: "};
	const std::vector<std::wstring> m_StatLabels{ L"Attack", L"Strength", L"Intelligence", L"Speed", L"Dexterity", L"Stamina"};

protected:
	std::wstring m_sName, m_sID;
	int m_Level, m_XP, m_XPToNextLevel, m_HP, m_MaxHP;
	bool m_bDead;
	ActorType m_eActorType;
	Stats m_Stats;

	//std::unordered_map<Equipment::EquipType, std::shared_ptr<Equipment>> m_mapEquipment;
	std::unordered_map<Stats::EquipSlots, std::shared_ptr<Equipment>>m_mapEquipmentSlots;
	
	// TODO: 
	/*
	map to equipment type of equipped items -- need equipment
	stats=create class
	actions
	*/
public: 
	Actor();
	Actor(const std::wstring& name, const std::wstring& id, int level, int max_hp, ActorType type=ActorType::MARINE);
	~Actor() = default;
	
	
	inline const int GetHP() const { return m_HP; }
	inline const int GetMaxHP() const { return m_MaxHP; }

	inline const std::vector<std::wstring> GetEquipSlotLabels() const { return m_EquipmentSlotsLabels; }
	inline const std::vector<std::wstring>& GetStatLabels() const { return m_StatLabels; }
	//std::unordered_map<Equipment::EquipType, std::shared_ptr<Equipment>>& GetEquippedItems() {return m_mapEquipment;}
	std::unordered_map<Stats::EquipSlots, std::shared_ptr<Equipment>>& GetEquippedItemSlots() 
	{ 
		return m_mapEquipmentSlots; 
	}

	Stats& GetStats() { return m_Stats; }

	inline const bool IsDead() const { return m_bDead; }
	inline const std::wstring& GetName() const { return m_sName; }
	inline const std::wstring& GetID() const { return m_sID; }
	const int GetLevel() const { return m_Level; }
	const int GetXP() const { return m_XP; }
	//const int GetMaxMP() const { return m_MaxMP; }
	const int GetXPToNextLevel() const { return m_XPToNextLevel; }


	void HealHp(int hp);
	void TakeDamage(int hp);
	
};