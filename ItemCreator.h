#pragma once
#include <memory>
#include <string>
#include <concepts>
#include "../Item.h"
#include "../Equipment.h"

class ItemCreator
{
private: 
	template <typename T, typename ...Args>
	requires std::constructible_from<T, Args...>
	static std::shared_ptr<T> Create(Args&& ...args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template <typename T, typename ...Args>
	static std::shared_ptr<T> Create(Args&& ...args)
	{
		return nullptr;
	}
public:
	template <class ...Args>
	static std::shared_ptr<Item> CreateItem(Item::ItemType type, Args&& ...args)
	{
		switch (type)
		{
		case Item::ItemType::HEALTH:
			return Create<Potion>(std::forward<Args>(args)...);
		case Item::ItemType::REVIVE:
			return nullptr; //nullptrs are placeholders for now.
		case Item::ItemType::STATUS_AFFECT:
			return nullptr;
		case Item::ItemType::BATTLE:
			return nullptr;
		case Item::ItemType::KEY_ITEMS:
			return nullptr;
		case Item::ItemType::NO_TYPE:
			return nullptr;
		default:
			return nullptr;
		}
	}
	template<class ...Args>
	static std::shared_ptr<Equipment> CreateEquipment(Equipment::EquipType type, WeaponProperties weapon_props,
		ArmorProperties armor_props, StatModifier stat_mod, Args&& ...args)
	{
		switch (type)
		{
		case Equipment::EquipType::WEAPON:
			return Create<Weapon>(std::forward<Args>(args)..., weapon_props, stat_mod);
		//case Equipment::EquipType::WEAPON:
		case Equipment::EquipType::ARMOR:
			return Create<Armor>(std::forward<Args>(args)...,armor_props, stat_mod);
		case Equipment::EquipType::ACCESSORY:
			//to do returns once made
			return nullptr;
		case Equipment::EquipType::NO_TYPE:
			return nullptr;
		default:
			return nullptr;
		}
	}
};
