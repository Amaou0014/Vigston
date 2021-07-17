#pragma once

#include "direct3d.h"

#include <map>

// 読み込んだ画像のナンバー
struct AnimationNum {
	unsigned int numU;
	unsigned int numV;
};

// 画像描画クラス
class Image
{
public:
	// テクスチャリスト
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

	// スプライト描画クラス
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

	// スプライトクラスのリスト
	std::map<const char*, Sprite*> spriteList;

	// コンストラクタ
	Image();
	// デストラクタ
	~Image();

	// 画像データ読み込み
	bool Load(const char* keyname, IDirect3DDevice9* pDevice3D, TCHAR* FileName);
	// 画像描画の座標セット
	void Set_Pos(const char* keyname, float x, float y);
	// 画像描画のサイズセット
	void Set_Size(const char* keyname, int Width, int Height);
	// 画像描画の角度セット
	void Set_Rotate(const char* keyname, float Rotate);

	// 画像の透過範囲を透過
	void SetRenderState(IDirect3DDevice9* pD3DDevice, RENDERSTATE RenderState);

	// 画像描画の座標X取得
	float Get_PosX(const char* keyname);
	// 画像描画の座標Y取得
	float Get_PosY(const char* keyname);
	// 画像描画の横幅取得
	int Get_Width(const char* keyname);
	// 画像描画の縦幅取得
	int Get_Height(const char* keyname);
	// 画像描画の角度取得
	float Get_Rotate(const char* keyname);

	// 画像描画の座標変更
	void Move_Pos(const char* keyname, float x, float y);
	// 画像描画の角度変更
	void Move_Rotate(const char* keyname, float Rotate);

	// 画像を分割して保存 ＊マップチップなどに使う
	void Set_Divide(const char* keyname, unsigned int DivU, unsigned int DivV);
	// 画像を分割して保存した画像を並べる
	void Set_UVNum(const char* keyname, unsigned int NumU, unsigned int NumV);
	// 指定されたキーで保存されている画像を描画
	void Draw(const char* keyname, IDirect3DDevice9* pDevice3D, bool isTurn = false);
};

// スプライトの当たり判定
bool IsHit(const char* keyname);