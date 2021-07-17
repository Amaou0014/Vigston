#pragma once

#include "direct3d.h"

#include <vector>
#include <tchar.h>
#include <map>


// テキスト描画クラス
class Text
{
private:
	// テキスト情報の構造体
	struct Info
	{
		ID3DXFont* pFont;  // Direct3Dフォント
		RECT				Rect;  // 描画領域
		std::vector<TCHAR>	 Buf;  // 文字列バッファ
	};
	// テキスト情報の構造体のポインタ
	Info* info;
public:

	// コンストラクタ
	Text();
	// デストラクタ
	virtual ~Text();

	// フォント作成
	bool Create(IDirect3DDevice9* pD3DDevice, int size = 16);

	// 文字列の描画
	void Draw(int x, int y, DWORD color, const TCHAR* str, va_list args);
};