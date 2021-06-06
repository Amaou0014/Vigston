#include "texture.h"

Texture::Texture(){
	pTexture = NULL;
}
Texture::~Texture()
{
	// �ǂݍ��܂�Ă�����j��
	if(pTexture != NULL)
		pTexture->Release();
}
bool Texture::Load(const char* name)
{
	Direct3D direct3d;

	// �摜�ǂݍ���
	// DirextX��WindowsAPI�̊֐���HRESULT�����ʂɕԂ��֐�������
	// FAILED�}�N���Ŋ֐������s�������킩��
	// SUCEEDED�}�N���Ŋ֐��������������킩��
	if(FAILED(D3DXCreateTextureFromFile(direct3d.pDevice3D, (TCHAR*)name, &pTexture)))
		return false;	// �摜�ǂݍ��ݎ��s�i�t�@�C�����Ȃ��\������j

	// �摜�ǂݍ��ݐ���
	return true;
}
