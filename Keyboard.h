#pragma once
#include <string>
#include "Button.h"
#include "Keys.h"
class Keyboard
{
private:
	Button m_Keys[KEY_LAST];
public:
	Keyboard();
	~Keyboard() = default;

	void Update();
	void OnKeyDown(int key);
	void OnKeyUp(int key);

	bool IsKeyHeld(int key) const;
	bool IsKeyJustPressed(int key) const;
	bool IsKeyJustReleased(int key) const;
};