#include "keyboard.h"


bool GetKey(int key)
{
	return GetAsyncKeyState(key);
}

bool PushKey(int key)
{
	if (GetAsyncKeyState(key))
	{
		if (!flg_p)
		{
			flg_p = true;

			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		flg_p = false;
	}
}

bool ReleaseKey(int key)
{
	if (GetAsyncKeyState(key))
	{
		flg_r = true;
		return false;
	}
	else
	{
		if (!flg_r)
		{
			return false;
		}
		else
		{
			flg_r = false;
			return true;
		}
	}
}