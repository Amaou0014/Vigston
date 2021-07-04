#include "device.h"


Device::Device()
{
}

Device::~Device()
{
}

void Device::GetMouseState()
{
	GetCursorPos(&pos);
}

int Device::GetMouseX()
{
	return pos.x;
}

int Device::GetMouseY()
{
	return pos.y;
}

void Device::GetKeyState()
{
	for (int i = 0; i < 256; i++)
	{
		keybuf[i] = key[i];
	}

	if (!GetKeyboardState(key))
	{

	}
}

bool Device::GetKey(unsigned char keycode)
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

bool Device::PushKey(unsigned char keycode)
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

bool Device::ReleaseKey(unsigned char keycode)
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