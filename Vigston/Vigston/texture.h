#pragma once

#include "direct3d.h"

// テクスチャクラス
class Texture
{
public:
	IDirect3DTexture9* pTexture;
	// コンストラクタ
	Texture();
	// デストラクタ
	~Texture();
	// 画像データ読み込み
	bool Load(IDirect3DDevice9* pDevice3D, TCHAR* FileName);
};