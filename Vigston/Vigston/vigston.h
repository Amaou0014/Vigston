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
	Keyboard keyboard;

	Wave wave_retoro1;
	SoundBuffer sb_retolo1;

	bool flag = false;

	const TCHAR* WC_BASIC = _T("BASIC_WINDOW");
	WNDCLASSEX wcex;

	int WINDOW_WIDTH;
	int WINDOW_HEIGHT;

	HWND hWnd;

	Vigston();
	~Vigston();

	// 初期化
	void Init(HWND hWnd);
	// Updateの前に一回だけ呼ばれる
	void Start();
	// 毎フレーム呼ばれる
	void Update();

	// 画像読み込み
	bool LoadTexture(TCHAR* name, Texture* texture);

	// 音声読み込み
	bool LoadSound(TCHAR* name, Wave* wave, SoundBuffer* sb);
	// 音量変更
	void ChangeVolume(long _volume, SoundBuffer* sb);

	// 描画位置セット
	void SetSprite(float x, float y, int width, int height, float rotate, Sprite* sprite);
};