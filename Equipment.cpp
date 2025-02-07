#include "Equipment.h"
#include "Player.h"
#include "Logger.h"
Weapon::Weapon()
	:Weapon(L"Weapon Name", L"Weapon description", 0,0)
{
}

Weapon::Weapon(const std::wstring& name, const std::wstring& description, int buy_price, int sell_price, WeaponProperties weapon_properties, StatModifier stat_modifier)
{
	m_sName = name;
	m_sDescription = description;
	m_BuyPrice = buy_price;
	m_SellPrice = sell_price;
	m_StatModifier = stat_modifier;
	SetEquipType(EquipType::WEAPON);
	m_WeaponProperties = weapon_properties;
	m_ArmorProperties = ArmorProperties();

}

bool Weapon::OnEquip(Player& player)
{
	const auto& item_pwr = GetValue();
	auto& player_stats = player.GetStats();

	//Se the weapon pwr
	player_stats.SetEquipmentValue(Stats::EquipSlots::WEAPON, item_pwr);
	const auto& stat_modifier = GetStatModifier();

	if (stat_modifier.modifierType != StatModifier::ModifierType::NO_TYPE)
		player_stats.SetModifier(stat_modifier.modifierTypeStr, stat_modifier.statModifierVal);
	

	//Equip the item
	Equip();
	player_stats.UpdateStats();
	return true;
}

bool Weapon::OnRemove(Player& player)
{
	auto& player_stats = player.GetStats();
	player_stats.SetEquipmentValue(Stats::EquipSlots::WEAPON, 0);

	const auto& stat_modifier = GetStatModifier();

	if (stat_modifier.modifierType != StatModifier::ModifierType::NO_TYPE)
		player_stats.SetModifier(stat_modifier.modifierTypeStr,0);

	Remove();
	player_stats.UpdateStats();
	return false;
}

Armor::Armor()
	:Armor(L"Armor Name", L"Armor Description",0,0)
{
}

Armor::Armor(const std::wstring& name, const std::wstring& description, int buy_price, int sell_price, ArmorProperties armor_properties, StatModifier stat_modifier)
{
	m_sName = name;
	m_sDescription = description;
	m_BuyPrice = buy_price; 
	m_SellPrice = sell_price;
	m_StatModifier = stat_modifier;
	SetEquipType(EquipType::ARMOR);
	m_WeaponProperties = WeaponProperties();
	m_ArmorProperties = armor_properties;

}

bool Armor::OnEquip(Player& player)
{
	const auto& item_pwr = GetValue();
	auto& player_stats = player.GetStats();
	Stats::EquipSlots slot = Stats::EquipSlots::NO_SLOT;
	switch (m_ArmorProperties.armorType)
	{
		case ArmorProperties:: ArmorType:: HEADGEAR:
			slot = Stats::EquipSlots::HEADGEAR;
			break;
		case ArmorProperties::ArmorType::CHEST_BODY:
			slot = Stats::EquipSlots::CHEST_BODY;
			break;
		case ArmorProperties::ArmorType::FOOTWEAR:
			slot = Stats::EquipSlots::FOOTWEAR;
			break;
		case ArmorProperties::ArmorType::NOT_ARMOR:
			slot = Stats::EquipSlots::NO_SLOT;
			return false;
		default:
			slot = Stats:: EquipSlots::NO_SLOT;
			return false;
	}

	//Get the stat modifier
	const auto& stat_modifier = GetStatModifier();

	if (stat_modifier.modifierType != StatModifier::ModifierType::NO_TYPE)
		player_stats.SetModifier(stat_modifier.modifierTypeStr, stat_modifier.statModifierVal);

	player_stats.SetEquipmentValue(slot, item_pwr);
	Equip();
	player_stats.UpdateStats();

	return true;
}

bool Armor::OnRemove(Player& player)
{
	auto& player_stats = player.GetStats();
	Stats::EquipSlots slot = Stats::EquipSlots::NO_SLOT;
	switch (m_ArmorProperties.armorType)
	{
	case ArmorProperties::ArmorType::HEADGEAR:
		slot = Stats::EquipSlots::HEADGEAR;
		break;
	case ArmorProperties::ArmorType::CHEST_BODY:
		slot = Stats::EquipSlots::CHEST_BODY;
		break;
	case ArmorProperties::ArmorType::FOOTWEAR:
		slot = Stats::EquipSlots::FOOTWEAR;
		break;
	case ArmorProperties::ArmorType::NOT_ARMOR:
		slot = Stats::EquipSlots::NO_SLOT;
		return false;
	default:
		slot = Stats::EquipSlots::NO_SLOT;
		return false;
	}

	//Get the stat modifier
	const auto& stat_modifier = GetStatModifier();

	if (stat_modifier.modifierType != StatModifier::ModifierType::NO_TYPE)
		player_stats.SetModifier(stat_modifier.modifierTypeStr, 0);

	player_stats.SetEquipmentValue(slot, 0);
	Remove();
	player_stats.UpdateStats();

	return true;
}
