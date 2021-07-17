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
	HFONT	hFont = NULL;	// �t�H���g�n���h��
	LOGFONT	LogFont = {};	// �t�H���g�\����

	// �f�t�H���g�t�H���g�擾
	hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	// �f�t�H���g�t�H���g���擾
	GetObject(hFont, sizeof(LOGFONT), &LogFont);
	// DirectX�t�H���g�쐬
	if (FAILED(D3DXCreateFont(pD3DDevice,
		size,						// ��������
		LogFont.lfWidth,			// ������
		LogFont.lfWeight,			// �t�H���g�̑���
		0,							// �~�b�v�}�b�v���x��
		LogFont.lfItalic,			// �C�^���b�N�t���O
		LogFont.lfCharSet,			// �����Z�b�g
		LogFont.lfOutPrecision,		// ���ۂ̃t�H���g�ƖړI�̃t�H���g�̓����̈�v���@
		LogFont.lfQuality,			// �N�H���e�B
		LogFont.lfPitchAndFamily,	// �s�b�`�ƃt�@�~���C���f�b�N�X
		LogFont.lfFaceName,			// �t�H���g��
		&info->pFont)))
	{
		return false;
	}


	return true;
}


// ������̕`��
void Text::Draw(int x, int y, DWORD color, const TCHAR* str, va_list args)
{
	int len = _vsctprintf(str, args) + 1;	// �������J�E���g�A�k��������������
	if (info->Buf.size() < (UINT)len)
		info->Buf.resize(len);					// �����T�C�Y�����I�Ƀ������m��
	_vstprintf(&info->Buf[0], str, args);			// �����𐮌`����

	SetRect(&info->Rect, 0, 0, 0, 0);
	// �`��̈�T�C�Y�擾
	info->pFont->DrawText(NULL, &info->Buf[0], -1, &info->Rect, DT_LEFT | DT_CALCRECT, color);
	// �{�`��
	info->Rect.left += x;
	info->Rect.right += x;
	info->Rect.top += y;
	info->Rect.bottom += y;
	info->pFont->DrawText(NULL, &info->Buf[0], -1, &info->Rect, DT_LEFT, color);
}