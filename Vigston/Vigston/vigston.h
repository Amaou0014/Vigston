#pragma once

#include "direct3d.h"
#include "texture.h"
#include "sprite.h"
#include "text.h"
#include "directsound.h"
#include "wave.h"
#include "soundbuffer.h"
#include "keyboard.h"


class Vigston
{
public:
	Direct3D	direct3d;
	DirectSound	directsound;

	Texture texture;
	Sprite sprite;

	Wave wave_retoro1;
	SoundBuffer sb_retolo1;

	Wave wave_retoro2;
	SoundBuffer sb_retolo2;

	bool flag = false;

	const TCHAR* WC_BASIC = _T("BASIC_WINDOW");
	WNDCLASSEX wcex;

	int WINDOW_WIDTH;
	int WINDOW_HEIGHT;

	HWND hWnd;

	DWORD backColor;

	Vigston();
	~Vigston();

	//この関数の中に処理を書いてね
	/////////////////////////////////

	// 初期化
	void Init(HWND hWnd);
	// Updateの前に一回だけ呼ばれる
	void Start();
	// 毎フレーム呼ばれる
	void Update();

	/////////////////////////////////

	// 背景色セット(十六進数)
	void Set_BackColor(unsigned int color);

	// 画面リセット
	void Clear_Screen();

	// レンダリング開始
	bool Begine_Scene();
	// レンダリング終了
	bool End_Scene();

	// 画像読み込み
	bool Load_Texture(TCHAR* name, Texture* texture);

	// 音声読み込み
	bool Load_Sound(TCHAR* name, Wave* wave, SoundBuffer* sb);
	// 音声再生
	void Play_Sound(bool isLoop, SoundBuffer* sb);
	// 音量変更
	void Set_Volume(long _volume, SoundBuffer* sb);
	// 音量取得
	long Get_Volume(SoundBuffer* sb);

	// 描画位置セット
	void Set_Sprite(float x, float y, int width, int height, float rotate, Sprite* sprite);
	// 描画位置を動かす
	void Move_Sprite(float x, float y, float rotate, Sprite* sprite);
	// 描画する
	void Draw(Texture* texture, Sprite* sprite);
};