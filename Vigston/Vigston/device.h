#pragma once

#include <Windows.h>

#define KEY_CODE_LEFTMOUSE              0x01
#define KEY_CODE_RIGHTMOUSE             0x02
#define KEY_CODE_Break                  0x03
#define KEY_CODE_SENTERMOUSE            0x04
#define KEY_CODE_BACKSPACE              0x08
#define KEY_CODE_TAB                    0x08
#define KEY_CODE_CLEAR                  0x0C
#define KEY_CODE_RETURN                 0x0D
#define KEY_CODE_SHIFT                  0x10
#define KEY_CODE_CONTROL                0x11
#define KEY_CODE_ALT                    0x12
#define KEY_CODE_PAUSE                  0x13
#define KEY_CODE_CAPSLOCK               0x14
#define KEY_CODE_ESCAPE                 0x1B
#define KEY_CODE_SPACE                  0x20
#define KEY_CODE_PAGEUP                 0x21
#define KEY_CODE_PAGEDAWN               0x22
#define KEY_CODE_END                    0x23
#define KEY_CODE_HOME                   0x24
#define KEY_CODE_LEFT                   0x25
#define KEY_CODE_UP                     0x26
#define KEY_CODE_RIGHT                  0x27
#define KEY_CODE_DOWN                   0x28
#define KEY_CODE_SELECT                 0x29
#define KEY_CODE_PRINT                  0x2A
#define KEY_CODE_EXECUTE                0x2B
#define KEY_CODE_PRINTSCREEN            0x2C
#define KEY_CODE_INSERT                 0x2D
#define KEY_CODE_DELETE                 0x2E
#define KEY_CODE_HELP                   0x2F
#define KEY_CODE_0                      0x30
#define KEY_CODE_1                      0x31
#define KEY_CODE_2                      0x32
#define KEY_CODE_3                      0x33
#define KEY_CODE_4                      0x34
#define KEY_CODE_5                      0x35
#define KEY_CODE_6                      0x36
#define KEY_CODE_7                      0x37
#define KEY_CODE_8                      0x38
#define KEY_CODE_9                      0x39
#define KEY_CODE_A                      0x41
#define KEY_CODE_B                      0x42
#define KEY_CODE_C                      0x43
#define KEY_CODE_D                      0x44
#define KEY_CODE_E                      0x45
#define KEY_CODE_F                      0x46
#define KEY_CODE_G                      0x47
#define KEY_CODE_H                      0x48
#define KEY_CODE_I                      0x49
#define KEY_CODE_J                      0x4A
#define KEY_CODE_K                      0x4B
#define KEY_CODE_L                      0x4C
#define KEY_CODE_M                      0x4D
#define KEY_CODE_N                      0x4E
#define KEY_CODE_O                      0x4F
#define KEY_CODE_P                      0x50
#define KEY_CODE_Q                      0x51
#define KEY_CODE_R                      0x52
#define KEY_CODE_S                      0x53
#define KEY_CODE_T                      0x54
#define KEY_CODE_U                      0x55
#define KEY_CODE_V                      0x56
#define KEY_CODE_W                      0x57
#define KEY_CODE_X                      0x58
#define KEY_CODE_Y                      0x59
#define KEY_CODE_Z                      0x5A
#define KEY_CODE_LEFTWINDOWS            0x5B
#define KEY_CODE_RIGHTWINDOWS           0x5C
#define KEY_CODE_APPLICATION            0x5D
#define KEY_CODE_SLEEP                  0x5F
#define KEY_CODE_NUMPAD0                0x60
#define KEY_CODE_NUMPAD1                0x61
#define KEY_CODE_NUMPAD2                0x62
#define KEY_CODE_NUMPAD3                0x63
#define KEY_CODE_NUMPAD4                0x64
#define KEY_CODE_NUMPAD5                0x65
#define KEY_CODE_NUMPAD6                0x66
#define KEY_CODE_NUMPAD7                0x67
#define KEY_CODE_NUMPAD8                0x68
#define KEY_CODE_NUMPAD9                0x69
#define KEY_CODE_MULTIPLY               0x6A
#define KEY_CODE_ADD                    0x6B
#define KEY_CODE_SEPARATOR              0x6C
#define KEY_CODE_SUBSTRACT              0x6D
#define KEY_CODE_DECIMAL                0x6E
#define KEY_CODE_DIVIDE                 0x6F
#define KEY_CODE_F1                     0x70
#define KEY_CODE_F2                     0x71
#define KEY_CODE_F3                     0x72
#define KEY_CODE_F4                     0x73
#define KEY_CODE_F5                     0x74
#define KEY_CODE_F6                     0x75
#define KEY_CODE_F7                     0x76
#define KEY_CODE_F8                     0x77
#define KEY_CODE_F9                     0x78
#define KEY_CODE_F10                    0x79
#define KEY_CODE_F11                    0x7A
#define KEY_CODE_F12                    0x7B
#define KEY_CODE_F13                    0x7C
#define KEY_CODE_F14                    0x7D
#define KEY_CODE_F15                    0x7E
#define KEY_CODE_F16                    0x7F
#define KEY_CODE_F17                    0x80
#define KEY_CODE_F18                    0x81
#define KEY_CODE_F19                    0x82
#define KEY_CODE_F20                    0x83
#define KEY_CODE_F21                    0x84
#define KEY_CODE_F22                    0x85
#define KEY_CODE_F23                    0x86
#define KEY_CODE_F24                    0x87
#define KEY_CODE_NUMLOCK                0x90
#define KEY_CODE_SCROLL                 0x91
#define KEY_CODE_LEFTSHIFT              0xA0
#define KEY_CODE_RIGHTSHIFT             0xA1
#define KEY_CODE_LEFTCONTROL            0xA2
#define KEY_CODE_RIGHTCONTROL           0xA3
#define KEY_CODE_LEFTMENU               0xA4
#define KEY_CODE_RIGHTMENU              0xA5
#define KEY_CODE_BROWSER_BACK           0xA6
#define KEY_CODE_BROWSER_FORWARD        0xA7
#define KEY_CODE_BROWSER_REFRESH        0xA8
#define KEY_CODE_BROWSER_STOP           0xA9
#define KEY_CODE_BROWSER_SEARCH         0xAA
#define KEY_CODE_BROWSER_FAVORITES      0xAB
#define KEY_CODE_BROWSER_HOME           0xAC
#define KEY_CODE_VOLUME_MUTE            0xAD
#define KEY_CODE_VOLUME_DOWN            0xAE
#define KEY_CODE_VOLUME_UP              0xAF
#define KEY_CODE_MEDIA_NEXT_TRACK       0xB0
#define KEY_CODE_MEDIA_PREV_TRACK       0xB1
#define KEY_CODE_MEDIA_STOP             0xB2
#define KEY_CODE_MEDIA_PLAY_PAUSE       0xB3
#define KEY_CODE_LAUNCH_MAIL            0xB4
#define KEY_CODE_LAUNCH_MEDIA_SELECT    0xB5
#define KEY_CODE_LAUNCH_APP1            0xB6
#define KEY_CODE_LAUNCH_APP2            0xB7
#define KEY_CODE_OEM_1                  0xBA
#define KEY_CODE_OEM_PLUS               0xBB
#define KEY_CODE_OEM_COMMA              0xBC
#define KEY_CODE_OEM_MINUS              0xBD
#define KEY_CODE_OEM_PERIOD             0xBE
#define KEY_CODE_OEM_2                  0xBF
#define KEY_CODE_OEM_3                  0xC0
#define KEY_CODE_OEM_4                  0xDB
#define KEY_CODE_OEM_5                  0xDC
#define KEY_CODE_OEM_6                  0xDD
#define KEY_CODE_OEM_7                  0xDE
#define KEY_CODE_OEM_8                  0xDF
#define KEY_CODE_OEM_102                0xE2
#define KEY_CODE_PROCESSKEY             0xE5
#define KEY_CODE_PACKET                 0xE7
#define KEY_CODE_ATTN                   0xF6
#define KEY_CODE_CRSEL                  0xF7
#define KEY_CODE_EXSEL                  0xF8
#define KEY_CODE_EREOF                  0xF9
#define KEY_CODE_PLAY                   0xFA
#define KEY_CODE_ZOOM                   0xFB
#define KEY_CODE_NONAME                 0xFC
#define KEY_CODE_PA1                    0xFD
#define KEY_CODE_OEM_CLEAR              0xFE

class Device
{
public:
	Device();
	~Device();
public:
	// 現在のマウス情報取得
	void GetMouseState();
	// マウスX座標取得
	int GetMouseX();
	// マウスY座標取得
	int GetMouseY();
public:
	// 現在のキー入力取得
	void GetKeyState();
	// 指定されたキーが押されているのか
	bool GetKey(unsigned char keycode);
	// 指定されたキーが押された瞬間
	bool PushKey(unsigned char keycode);
	// 指定されたキーが離れた瞬間
	bool ReleaseKey(unsigned char keycode);

private:
	POINT pos;

	const int isInputNum = 0x80;
	BYTE key[256];      // 今のフレームでのキー入力情報
	BYTE keybuf[256];   // 一個前のフレームでのキー入力情報
};