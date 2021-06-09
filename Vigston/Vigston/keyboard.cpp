#include "keyboard.h"


bool GetKey(int key)
{
	return GetAsyncKeyState(key);
}

bool PushKey(int key)
{
	if (GetAsyncKeyState(key))
	{
		if (!flg_push)
		{
			flg_push = true;

			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		flg_push = false;
	}
}

bool ReleaseKey(int key)
{
	if (GetAsyncKeyState(key))
	{
		flg_release = true;
		return false;
	}
	else
	{
		if (!flg_release)
		{
			return false;
		}
		else
		{
			flg_release = false;
			return true;
		}
	}
}