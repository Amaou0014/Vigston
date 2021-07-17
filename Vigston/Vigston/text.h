#pragma once

#include "direct3d.h"

#include <vector>
#include <tchar.h>
#include <map>


// �e�L�X�g�`��N���X
class Text
{
private:
	// �e�L�X�g���̍\����
	struct Info
	{
		ID3DXFont* pFont;  // Direct3D�t�H���g
		RECT				Rect;  // �`��̈�
		std::vector<TCHAR>	 Buf;  // ������o�b�t�@
	};
	// �e�L�X�g���̍\���̂̃|�C���^
	Info* info;
public:

	// �R���X�g���N�^
	Text();
	// �f�X�g���N�^
	virtual ~Text();

	// �t�H���g�쐬
	bool Create(IDirect3DDevice9* pD3DDevice, int size = 16);

	// ������̕`��
	void Draw(int x, int y, DWORD color, const TCHAR* str, va_list args);
};