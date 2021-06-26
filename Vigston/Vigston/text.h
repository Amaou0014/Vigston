#pragma once

#include "direct3d.h"
#include <vector>
#include <tchar.h>


// テキスト描画クラス
class Text
{
private:
	ID3DXFont*         pFont;  // Direct3Dフォント
	RECT				Rect;  // 描画領域
	std::vector<TCHAR>	 Buf;  // 文字列バッファ
public:

	Text();
	virtual ~Text();

	// DirectXフォント作成
	bool Create(IDirect3DDevice9* pD3DDevice, int size = 16);

	// 文字列の描画
	void Draw( int x, int y, DWORD color, const TCHAR* str, ...);
};