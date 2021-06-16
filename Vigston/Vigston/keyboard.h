#pragma once

#include <Windows.h>

#define KEY_CODE_LEFTMOUSE 0x01
#define KEY_CODE_RIGHTMOUSE 0x02
#define KEY_CODE_Break 0x03
#define KEY_CODE_SENTERMOUSE 0x04
#define KEY_CODE_BACKSPACE 0x08
#define KEY_CODE_TAB 0x08
#define KEY_CODE_CLEAR 0x0C
#define KEY_CODE_RETURN 0x0D
#define KEY_CODE_SHIFT 0x10
#define KEY_CODE_CONTROL 0x11
#define KEY_CODE_ALT 0x12
#define KEY_CODE_PAUSE 0x13
#define KEY_CODE_CAPSLOCK 0x14
#define KEY_CODE_ESCAPE 0x1B
#define KEY_CODE_SPACE 0x20
#define KEY_CODE_PAGEUP 0x21
#define KEY_CODE_PAGEDAWN 0x22
#define KEY_CODE_END 0x23
#define KEY_CODE_HOME 0x24
#define KEY_CODE_LEFT 0x25
#define KEY_CODE_UP 0x26
#define KEY_CODE_RIGHT 0x27
#define KEY_CODE_DOWN 0x28
#define KEY_CODE_SELECT 0x29
#define KEY_CODE_PRINT 0x2A
#define KEY_CODE_EXECUTE 0x2B
#define KEY_CODE_PRINTSCREEN 0x2C
#define KEY_CODE_INSERT 0x2D
#define KEY_CODE_DELETE 0x2E
#define KEY_CODE_HELP 0x2F
#define KEY_CODE_0 0x30
#define KEY_CODE_1 0x31
#define KEY_CODE_2 0x32
#define KEY_CODE_3 0x33
#define KEY_CODE_4 0x34
#define KEY_CODE_5 0x35
#define KEY_CODE_6 0x36
#define KEY_CODE_7 0x37
#define KEY_CODE_8 0x38
#define KEY_CODE_9 0x39
#define KEY_CODE_A 0x41
#define KEY_CODE_B 0x42
#define KEY_CODE_C 0x43
#define KEY_CODE_D 0x44
#define KEY_CODE_E 0x45
#define KEY_CODE_F 0x46
#define KEY_CODE_G 0x47
#define KEY_CODE_H 0x48
#define KEY_CODE_I 0x49
#define KEY_CODE_J 0x4A
#define KEY_CODE_K 0x4B
#define KEY_CODE_L 0x4C
#define KEY_CODE_M 0x4D
#define KEY_CODE_N 0x4E
#define KEY_CODE_O 0x4F
#define KEY_CODE_P 0x50
#define KEY_CODE_Q 0x51
#define KEY_CODE_R 0x52
#define KEY_CODE_S 0x53
#define KEY_CODE_T 0x54
#define KEY_CODE_U 0x55
#define KEY_CODE_V 0x56
#define KEY_CODE_W 0x57
#define KEY_CODE_X 0x58
#define KEY_CODE_Y 0x59
#define KEY_CODE_Z 0x5A
#define KEY_CODE_LEFTWINDOWS 0x5B
#define KEY_CODE_RIGHTWINDOWS 0x5C
#define KEY_CODE_APPLICATION 0x5D
#define KEY_CODE_
#define KEY_CODE_
#define KEY_CODE_
#define KEY_CODE_
#define KEY_CODE_
#define KEY_CODE_
#define KEY_CODE_
#define KEY_CODE_
#define KEY_CODE_
#define KEY_CODE_
#define KEY_CODE_
#define KEY_CODE_
#define KEY_CODE_

static unsigned char key[256];
static unsigned char keybuf[256];

static bool flg_p = false;
static bool trigger = false;

class Keyboard
{
public:
	void GetKeyState();
	bool GetKey(unsigned char key);
	bool PushKey(unsigned char key);
	bool ReleaseKey(int key);
};