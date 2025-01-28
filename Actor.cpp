#include "Actor.h"

Actor::Actor()
	:Actor(L"Actor_name",L"actor_ID", 1, 100, ActorType::MARINE)
{

}

Actor::Actor(const std::wstring& name, const std::wstring& id, int level, int max_hp, ActorType type)
	: m_sName{name}
	,m_sID{id}
	, m_Level{level}
	, m_XP{0}
	,m_XPToNextLevel{250}
	,m_HP{max_hp}
	, m_bDead{ false }
	, m_MaxHP{max_hp}
	,m_eActorType{type}

{
}

void Actor::HealHp(int hp)
{
	m_HP += hp;
	if (m_HP >= m_MaxHP)
		m_HP = m_MaxHP;
}

void Actor::TakeDamage(int hp)
{
	m_HP -= hp;
	if (m_HP <= 0)
	{
		m_HP = 0;
		m_bDead = true;
	}
}
