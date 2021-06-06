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
bool Texture::Load(const char* name)
{
	Direct3D direct3d;

	// 画像読み込み
	// DirextXやWindowsAPIの関数はHRESULTを結果に返す関数が多い
	// FAILEDマクロで関数が失敗したかわかる
	// SUCEEDEDマクロで関数が成功したかわかる
	if(FAILED(D3DXCreateTextureFromFile(direct3d.pDevice3D, (TCHAR*)name, &pTexture)))
		return false;	// 画像読み込み失敗（ファイルがない可能性あり）

	// 画像読み込み成功
	return true;
}
