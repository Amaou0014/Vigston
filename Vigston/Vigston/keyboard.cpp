#include "keyboard.h"


void Keyboard::GetKeyState()
{
	for (int i = 0; i < 256; i++)
	{
		keybuf[i] = key[i];
	}
	GetKeyboardState((PBYTE)keybuf);
	GetKeyboardState((PBYTE)key);
}

bool Keyboard::GetKey(unsigned char keycode)
{
	if (key[keycode] & 0x80)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Keyboard::PushKey(unsigned char keycode)
{
	if (key[keycode] & 0x80 && !(keybuf[keycode] & 0x80))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Keyboard::ReleaseKey(int key)
{
	if (key & 0x80)
	{
		return true;
	}
	else
	{
		return false;
	}
}