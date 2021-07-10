#pragma once

#include "direct3d.h"

class Image
{
public:
	IDirect3DTexture9* pTexture;
	// コンストラクタ
	Image();
	// デストラクタ
	~Image();
	// 画像データ読み込み
	bool Load(IDirect3DDevice9* pDevice3D, TCHAR* FileName);
};