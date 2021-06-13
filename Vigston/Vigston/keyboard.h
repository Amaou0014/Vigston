#pragma once

#include <Windows.h>

static bool flg_p = false;
static bool flg_r = false;

class Keyboard
{
public:
	bool GetKey(int key);

	bool PushKey(int key);

	bool ReleaseKey(int key);
};