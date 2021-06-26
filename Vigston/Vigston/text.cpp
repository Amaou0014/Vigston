#define _CRT_SECURE_NO_WARNINGS
#define  _CRT_NON_CONFORMING_SWPRINTFS
#include "text.h"

// コンストラクタ
Text::Text()
{
	pFont = NULL;
}

// デストラクタ
Text::~Text()
{
	if (pFont != NULL)
		pFont->Release();
}

// DirectXフォント作成
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
		size,					// 文字高さ
		LogFont.lfWidth,			// 文字幅
		LogFont.lfWeight,			// フォントの太さ
		0,							// ミップマップレベル
		LogFont.lfItalic,			// イタリックフラグ
		LogFont.lfCharSet,			// 文字セット
		LogFont.lfOutPrecision,		// 実際のフォントと目的のフォントの特性の一致方法
		LogFont.lfQuality,			// クォリティ
		LogFont.lfPitchAndFamily,	// ピッチとファミリインデックス
		LogFont.lfFaceName,			// フォント名
		&pFont)))
	{
		return false;
	}


	return true;
}


// 文字列の描画
void Text::Draw(int x, int y, DWORD color, const TCHAR* str, ...)
{
	va_list args;
	va_start(args, str);					// 可変引数の最初の要素を格納する
	int len = _vsctprintf(str, args) + 1;	// 文字数カウント、ヌル文字分加える
	if (Buf.size() < (UINT)len)
		Buf.resize(len);					// 文字サイズ分動的にメモリ確保
	_vstprintf(&Buf[0], str, args);			// 文字を整形する

	SetRect(&Rect, 0, 0, 0, 0);
	// 描画領域サイズ取得
	pFont->DrawText(NULL, &Buf[0], -1, &Rect, DT_LEFT | DT_CALCRECT, color);
	// 本描画
	Rect.left += x;
	Rect.right += x;
	Rect.top += y;
	Rect.bottom += y;
	pFont->DrawText(NULL, &Buf[0], -1, &Rect, DT_LEFT, color);
}