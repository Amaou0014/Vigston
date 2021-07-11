#pragma once

#include "direct3d.h"

struct AnimationNum {
	unsigned int numU;
	unsigned int numV;
};

class Image
{
public:
	IDirect3DTexture9* pTexture;

	// レンダーステートの設定
	enum RENDERSTATE
	{
		RENDER_DEFAULT,		// デフォルト(不透明)
		RENDER_ALPHATEST	// αテスト
	};
	// 板ポリゴン頂点情報
	struct Vertex {
		float x, y, z;// 3次元座標
		float rhw;	// 2D変換済みフラグ
		float u, v;	// UV座標
	};
	// FVF（柔軟な頂点構造体宣言）フラグ
	static const DWORD SPRITE_FVF = D3DFVF_XYZRHW | D3DFVF_TEX1;

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

	// コンストラクタ
	Image();
	// デストラクタ
	~Image();
	// 画像データ読み込み
	bool Load(IDirect3DDevice9* pDevice3D, TCHAR* FileName);

	void Set_Pos(float x, float y);
	void Set_Width(int Width, int Height);
	void Set_Rotate(float Rotate);

	void SetRenderState(IDirect3DDevice9* pD3DDevice, RENDERSTATE RenderState);

	float Get_PosX();
	float Get_PosY();
	int Get_Width();
	int Get_Height();
	float Get_Rotate();

	void Move_Pos(float x, float y);
	void Move_Rotate(float Rotate);

	void Set_Divide(unsigned int DivU, unsigned int DivV);
	void Set_UVNum(unsigned int NumU, unsigned int NumV);
	void Draw(IDirect3DDevice9* pDevice3D, IDirect3DTexture9* pTexture, bool isTurn = false);
};

// スプライトの当たり判定
bool IsHit(const Image& image1, const Image& image2);