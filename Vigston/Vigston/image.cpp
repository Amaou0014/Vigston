#include "image.h"

Image::Image() {
	pTexture = NULL;
}
Image::~Image()
{
	// �ǂݍ��܂�Ă�����j��
	if (pTexture != NULL)
		pTexture->Release();
}
bool Image::Load(IDirect3DDevice9* pDevice3D, TCHAR* FileName)
{
	// �摜�ǂݍ���
	if (FAILED(D3DXCreateTextureFromFile(pDevice3D, FileName, &pTexture)))
		return false;	// ���s

	// ����
	return true;
}