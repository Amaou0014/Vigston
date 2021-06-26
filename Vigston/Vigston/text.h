#pragma once

#include "direct3d.h"
#include <vector>
#include <tchar.h>


// �e�L�X�g�`��N���X
class Text
{
private:
	ID3DXFont*         pFont;  // Direct3D�t�H���g
	RECT				Rect;  // �`��̈�
	std::vector<TCHAR>	 Buf;  // ������o�b�t�@
public:

	Text();
	virtual ~Text();

	// DirectX�t�H���g�쐬
	bool Create(IDirect3DDevice9* pD3DDevice, int size = 16);

	// ������̕`��
	void Draw( int x, int y, DWORD color, const TCHAR* str, ...);
};