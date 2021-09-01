#pragma once

#include "direct3d.h"
#include "image.h"
#include "text.h"
#include "sound.h"
#include "device.h"
#include "window.h"


// ライブラリの基本クラス
// このクラス内のメソッドを使ってもらう
class Vigston
{
public:
	//各クラスオブジェクトポインタ
	Direct3D*	direct3d;
	Sound*		sound;
	Image*		image;
	Text*		text;
	Device*		device;
	Window*		window;

	// ウィンドウのメッセージ情報
	MSG msg = {};

	// ウィンドウの背景色
	DWORD backColor;

	// コンストラクタ
	Vigston();
	// デストラクタ
	~Vigston();

	//この関数の中に処理を書いてね
	/////////////////////////////////

	// 初期化
	void Init();

	/////////////////////////////////

	// ウィンドウセット
	void Set_Window(const TCHAR* name);
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
	bool Load_Image(const char* keyname, TCHAR* name, float x, float y, int width, int height, float rotate);
	// 画像を分割して読み込み
	bool LoadDiv_Image(const char* keyname, TCHAR* name, float x, float y, int width, int height, float rotate, unsigned int DivU, unsigned int DivV);
	// 描画位置セット
	void Set_Image(const char* keyname, float x, float y, int width, int height, float rotate);
	// 描画位置を動かす
	void Move_Image(const char* keyname, float x, float y, float rotate);
	// 描画座標X取得
	float Get_Image_PosX(const char* keyname);
	// 描画座標Y取得
	float Get_Image_PosY(const char* keyname);
	// 描画する
	void Draw_Image(const char* keyname, bool isTurn = false);

	// 音声読み込み
	bool Load_Sound(const char* keyname, TCHAR* name);
	// 音声再生
	void Play_Sound(const char* keyname, bool isLoop);
	// 音量変更
	void Set_Volume(const char* keyname, long _volume);
	// 音量取得
	long Get_Volume(const char* keyname);

	// フォント作成
	bool Create_Font(int size);
	// フォント描画
	void Draw_Font(int x, int y, DWORD color, const TCHAR* str...);

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