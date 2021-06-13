#include "texture.h"

Texture::Texture(){
	pTexture = NULL;
}
Texture::~Texture()
{
	// “Ç‚İ‚Ü‚ê‚Ä‚¢‚½‚ç”jŠü
	if(pTexture != NULL)
		pTexture->Release();
}
bool Texture::Load(IDirect3DDevice9* pDevice3D, TCHAR* FileName)
{
	// ‰æ‘œ“Ç‚İ‚İ
	if (FAILED(D3DXCreateTextureFromFile(pDevice3D, FileName, &pTexture)))
		return false;	// ¸”s

	// ¬Œ÷
	return true;
}
