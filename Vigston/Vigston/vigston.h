#pragma once

#include "direct3d.h"
#include "texture.h"
#include "sprite.h"
#include "text.h"
#include "directsound.h"
#include "wave.h"
#include "soundbuffer.h"


class Vigston
{
public:
	Direct3D	direct3d;
	DirectSound	directsound;

	Texture texture;

	Sprite sprite;

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

	// 描画位置セット
	void SetSprite(float x, float y, int width, int height, float rotate, Sprite* sprite);
};