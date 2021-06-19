#include "keyboard.h"


void Keyboard::GetKeyState()
{
	for (int i = 0; i < 256; i++)
	{
		keybuf[i] = key[i];
	}

	if (!GetKeyboardState(key))
	{

	}
}

bool Keyboard::GetKey(unsigned char keycode)
{
	if (key[keycode] & isInputNum)
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
	if (key[keycode] & isInputNum)
	{
		if (!(keybuf[keycode] & isInputNum))
		{
			return true;
		}
	}

	return false;
}

bool Keyboard::ReleaseKey(unsigned char keycode)
{
	if (!(key[keycode] & isInputNum))
	{
		if ((keybuf[keycode] & isInputNum))
		{
			return true;
		}
	}
	return false;
}