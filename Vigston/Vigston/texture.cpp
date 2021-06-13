#include "texture.h"

Texture::Texture(){
	pTexture = NULL;
}
Texture::~Texture()
{
	// 読み込まれていたら破棄
	if(pTexture != NULL)
		pTexture->Release();
}
bool Texture::Load(IDirect3DDevice9* pDevice3D, TCHAR* FileName)
{
	// 画像読み込み
	if (FAILED(D3DXCreateTextureFromFile(pDevice3D, FileName, &pTexture)))
		return false;	// 失敗

	// 成功
	return true;
}
