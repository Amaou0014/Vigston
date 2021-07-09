#pragma once

#include "direct3d.h"
#include "texture.h"
#include "sprite.h"
#include "text.h"
#include "sound.h"
#include "device.h"
#include "window.h"


class Vigston
{
public:
	Direct3D	direct3d;
	Sound* sound;

	Window window;

	MSG msg = {};

	Device device;

	bool flag = false;

	DWORD backColor;

	Vigston();
	~Vigston();

	//この関数の中に処理を書いてね
	/////////////////////////////////

	// 初期化
	void Init(HINSTANCE hInstance);

	/////////////////////////////////

	// ウィンドウセット
	void Set_Window(const TCHAR* name, const HINSTANCE hInst);
	// ウィンドウ座標セット
	void Set_Window_Pos(int x, int y);
	// ウィンドウ座標セット
	void Set_Window_Size(int w, int h);
	// ウィンドウ作成
	void Create_Window(LPCTSTR name, DWORD dwStyle, HWND hWndParent, HMENU hMenu);
	// メッセージループ
	bool GameQuit();
	// メッセージループ
	bool ProcessMessage();
	// 背景色セット(十六進数)
	void Set_BackColor(unsigned int color);

	// 画面リセット
	void Clear_Screen();

	// レンダリング開始
	bool Begine_Scene();
	// レンダリング終了
	bool End_Scene();
	// 描画反映
	void ScreenFlip();

	// 画像読み込み
	bool Load_Texture(TCHAR* name, Texture* texture);

	// 音声読み込み
	bool Load_Sound(const char* keyname, TCHAR* name);
	// 音声再生
	void Play_Sound(const char* keyname, bool isLoop);
	// 音量変更
	void Set_Volume(const char* keyname, long _volume);
	// 音量取得
	long Get_Volume(const char* keyname);

	// フォント作成
	bool Create_Font(int size, Text* text);
	// フォント描画
	void Draw_Font(int x, int y, DWORD color, Text* text, const TCHAR* str...);

	// 描画位置セット
	void Set_Sprite(float x, float y, int width, int height, float rotate, Sprite* sprite);
	// 描画位置を動かす
	void Move_Sprite(float x, float y, float rotate, Sprite* sprite);
	// 描画する
	void Draw_Image(Texture* texture, Sprite* sprite);

	// キー情報取得
	void GetKeyState();
	// キーが入力されているか
	bool GetKey(unsigned char keycode);
	// キーを押した瞬間
	bool PushKey(unsigned char keycode);
	// キーを離した瞬間
	bool ReleaseKey(unsigned char keycode);

	// マウス情報取得
	void GetMouseState();
	// マウスX座標取得
	int GetMouseX();
	// マウスY座標取得
	int GetMouseY();
};