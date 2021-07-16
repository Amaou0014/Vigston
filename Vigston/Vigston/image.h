#pragma once

#include "direct3d.h"

#include <map>

struct AnimationNum {
	unsigned int numU;
	unsigned int numV;
};

class Image
{
public:
	std::map<const char*, IDirect3DTexture9*> textureList;

	// レンダーステートの設定
	enum RENDERSTATE
	{
		RENDER_DEFAULT,		// デフォルト(不透明)
		RENDER_ALPHATEST,	// αテスト
		RENDER_HALFADD,		// 半加算合成
		RENDER_ADD			// 加算合成
	};

	// 板ポリゴン頂点情報
	struct Vertex {
		float x, y, z;// 3次元座標
		float rhw;	// 2D変換済みフラグ
		float u, v;	// UV座標
	};

	// FVF（柔軟な頂点構造体宣言）フラグ
	static const DWORD SPRITE_FVF = D3DFVF_XYZRHW | D3DFVF_TEX1;

	struct Sprite
	{
		// スプライト位置
		D3DXVECTOR2 pos;
		// スプライトサイズ
		int width;
		int height;
		// UVの分割数
		unsigned int divU;
		unsigned int divV;
		// UVの番号
		unsigned int numU;
		unsigned int numV;
		// 回転値（ラジアン）
		float rotate;
	};

	std::map<const char*, Sprite*> spriteList;

	//// スプライト位置
	//D3DXVECTOR2 pos;
	//// スプライトサイズ
	//int width;
	//int height;
	//// UVの分割数
	//unsigned int divU;
	//unsigned int divV;
	//// UVの番号
	//unsigned int numU;
	//unsigned int numV;
	//// 回転値（ラジアン）
	//float rotate;

	// コンストラクタ
	Image();
	// デストラクタ
	~Image();
	// 画像データ読み込み
	bool Load(const char* keyname, IDirect3DDevice9* pDevice3D, TCHAR* FileName);

	void Set_Pos(const char* keyname, float x, float y);
	void Set_Width(const char* keyname, int Width, int Height);
	void Set_Rotate(const char* keyname, float Rotate);

	void SetRenderState(IDirect3DDevice9* pD3DDevice, RENDERSTATE RenderState);

	float Get_PosX(const char* keyname);
	float Get_PosY(const char* keyname);
	int Get_Width(const char* keyname);
	int Get_Height(const char* keyname);
	float Get_Rotate(const char* keyname);

	void Move_Pos(const char* keyname, float x, float y);
	void Move_Rotate(const char* keyname, float Rotate);

	void Set_Divide(const char* keyname, unsigned int DivU, unsigned int DivV);
	void Set_UVNum(const char* keyname, unsigned int NumU, unsigned int NumV);
	void Draw(const char* keyname, IDirect3DDevice9* pDevice3D, bool isTurn = false);
};

// スプライトの当たり判定
bool IsHit(const char* keyname);