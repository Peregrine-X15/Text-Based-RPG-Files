#include "Keyboard.h"
#include "../Logger.h"
Keyboard::Keyboard()
{
	//nothing to do 
}

void Keyboard::Update()
{
	for (int i = 0; i < KEY_LAST; i++)
	{
		m_Keys[i].m_bisJustPressed=false;
		m_Keys[i].m_bIsJustReleased = false;
	}
}

void Keyboard::OnKeyDown(int key)
{
	//check to see if key is defined
	if (key > KEY_LAST)
	{
		TRPG_ERROR("[" + std::to_string(key) + "] - is not defined");
		return;
	}
	m_Keys[key].Update(true);
}

void Keyboard::OnKeyUp(int key)
{
	if (key > KEY_LAST)
	{
		TRPG_ERROR("[" + std::to_string(key) + "] - is not defined");
		return;
	}
	m_Keys[key].Update(false);
}

bool Keyboard::IsKeyHeld(int key) const
{
	if (key > KEY_LAST)
	{
		TRPG_ERROR("[" + std::to_string(key) + "] - is not defined");
		return false;
	}
	return m_Keys[key].m_bIsDown;
	
}

bool Keyboard::IsKeyJustPressed(int key) const
{
	if (key > KEY_LAST)
	{
		TRPG_ERROR("[" + std::to_string(key) + "] - is not defined");
		return false;
	}
	return m_Keys[key].m_bisJustPressed;
}

bool Keyboard::IsKeyJustReleased(int key) const
{
	if (key > KEY_LAST)
	{
		TRPG_ERROR("[" + std::to_string(key) + "] - is not defined");
		return false;
	}
	return m_Keys[key].m_bIsJustReleased;
}
