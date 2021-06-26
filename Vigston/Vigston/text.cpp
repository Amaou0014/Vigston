#define _CRT_SECURE_NO_WARNINGS
#define  _CRT_NON_CONFORMING_SWPRINTFS
#include "text.h"

// �R���X�g���N�^
Text::Text()
{
	pFont = NULL;
}

// �f�X�g���N�^
Text::~Text()
{
	if (pFont != NULL)
		pFont->Release();
}

// DirectX�t�H���g�쐬
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
		size,					// ��������
		LogFont.lfWidth,			// ������
		LogFont.lfWeight,			// �t�H���g�̑���
		0,							// �~�b�v�}�b�v���x��
		LogFont.lfItalic,			// �C�^���b�N�t���O
		LogFont.lfCharSet,			// �����Z�b�g
		LogFont.lfOutPrecision,		// ���ۂ̃t�H���g�ƖړI�̃t�H���g�̓����̈�v���@
		LogFont.lfQuality,			// �N�H���e�B
		LogFont.lfPitchAndFamily,	// �s�b�`�ƃt�@�~���C���f�b�N�X
		LogFont.lfFaceName,			// �t�H���g��
		&pFont)))
	{
		return false;
	}


	return true;
}


// ������̕`��
void Text::Draw(int x, int y, DWORD color, const TCHAR* str, ...)
{
	va_list args;
	va_start(args, str);					// �ψ����̍ŏ��̗v�f���i�[����
	int len = _vsctprintf(str, args) + 1;	// �������J�E���g�A�k��������������
	if (Buf.size() < (UINT)len)
		Buf.resize(len);					// �����T�C�Y�����I�Ƀ������m��
	_vstprintf(&Buf[0], str, args);			// �����𐮌`����

	SetRect(&Rect, 0, 0, 0, 0);
	// �`��̈�T�C�Y�擾
	pFont->DrawText(NULL, &Buf[0], -1, &Rect, DT_LEFT | DT_CALCRECT, color);
	// �{�`��
	Rect.left += x;
	Rect.right += x;
	Rect.top += y;
	Rect.bottom += y;
	pFont->DrawText(NULL, &Buf[0], -1, &Rect, DT_LEFT, color);
}