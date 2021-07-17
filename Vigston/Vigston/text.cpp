#define _CRT_SECURE_NO_WARNINGS
#define  _CRT_NON_CONFORMING_SWPRINTFS
#include "text.h"


Text::Text()
{
	info = new Info();
}

Text::~Text()
{
	delete info;
}


bool Text::Create(IDirect3DDevice9* pD3DDevice, int size)
{
	HFONT	hFont = NULL;	// フォントハンドル
	LOGFONT	LogFont = {};	// フォント構造体

	// デフォルトフォント取得
	hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	// デフォルトフォント情報取得
	GetObject(hFont, sizeof(LOGFONT), &LogFont);
	// DirectXフォント作成
	if (FAILED(D3DXCreateFont(pD3DDevice,
		size,						// 文字高さ
		LogFont.lfWidth,			// 文字幅
		LogFont.lfWeight,			// フォントの太さ
		0,							// ミップマップレベル
		LogFont.lfItalic,			// イタリックフラグ
		LogFont.lfCharSet,			// 文字セット
		LogFont.lfOutPrecision,		// 実際のフォントと目的のフォントの特性の一致方法
		LogFont.lfQuality,			// クォリティ
		LogFont.lfPitchAndFamily,	// ピッチとファミリインデックス
		LogFont.lfFaceName,			// フォント名
		&info->pFont)))
	{
		return false;
	}


	return true;
}


// 文字列の描画
void Text::Draw(int x, int y, DWORD color, const TCHAR* str, va_list args)
{
	int len = _vsctprintf(str, args) + 1;	// 文字数カウント、ヌル文字分加える
	if (info->Buf.size() < (UINT)len)
		info->Buf.resize(len);					// 文字サイズ分動的にメモリ確保
	_vstprintf(&info->Buf[0], str, args);			// 文字を整形する

	SetRect(&info->Rect, 0, 0, 0, 0);
	// 描画領域サイズ取得
	info->pFont->DrawText(NULL, &info->Buf[0], -1, &info->Rect, DT_LEFT | DT_CALCRECT, color);
	// 本描画
	info->Rect.left += x;
	info->Rect.right += x;
	info->Rect.top += y;
	info->Rect.bottom += y;
	info->pFont->DrawText(NULL, &info->Buf[0], -1, &info->Rect, DT_LEFT, color);
}