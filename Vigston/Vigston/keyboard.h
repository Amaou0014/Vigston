#pragma once

#include <Windows.h>


static bool flg_push = false;
static bool flg_release = false;

bool GetKey(int key);

bool PushKey(int key);

bool ReleaseKey(int key);