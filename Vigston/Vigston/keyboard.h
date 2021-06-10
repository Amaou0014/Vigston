#pragma once

#include <Windows.h>

static bool flg_p;
static bool flg_r;

class Keyboard
{
public:
	bool GetKey(int key);

	bool PushKey(int key);

	bool ReleaseKey(int key);
};