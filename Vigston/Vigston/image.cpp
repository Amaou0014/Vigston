#include "image.h"

#include <Windows.h>

#define DST_LEN (256)

Image::Image()
{
	if (!textureList.empty())
	{
		textureList.clear();
	}

	if (!spriteList.empty())
	{
		spriteList.clear();
	}
}
Image::~Image()
{
	// テクスチャ読み込まれていたら破棄
	for (auto tex = textureList.begin(); tex != textureList.end(); tex++)
	{
		if (tex->second != nullptr)
		{
			tex->second->Release();
			tex->second = nullptr;
		}
	}

	textureList.clear();

	// スプライト読み込まれていたら破棄
	for (auto sp = spriteList.begin(); sp != spriteList.end(); sp++)
	{
		if (sp->second != nullptr)
		{
			delete sp->second;
			sp->second = nullptr;
		}
	}

	spriteList.clear();
}
bool Image::Load(const char* keyname, IDirect3DDevice9* pDevice3D, TCHAR* FileName)
{
	if (spriteList[keyname] == NULL)
	{
		spriteList[keyname] = new Sprite();

		spriteList[keyname]->pos.x = 0.0f;
		spriteList[keyname]->pos.y = 0.0f;
		spriteList[keyname]->width = 0;
		spriteList[keyname]->height = 0;
		spriteList[keyname]->divU = 1;
		spriteList[keyname]->divV = 1;
		spriteList[keyname]->numU = 0;
		spriteList[keyname]->numV = 0;
		spriteList[keyname]->rotate = 0.0f;
	}
	// 画像読み込み
	if (FAILED(D3DXCreateTextureFromFile(pDevice3D, FileName, &textureList[keyname])))
	{
		return false;	// 失敗
	}
	else
	{
		// 成功
		return true;
	}
}

void Image::Set_Pos(const char* keyname, float x, float y)
{
	spriteList[keyname]->pos.x = x;
	spriteList[keyname]->pos.y = y;
}
void Image::Set_Size(const char* keyname, int Width, int Height)
{
	spriteList[keyname]->width = Width;
	spriteList[keyname]->height = Height;
}

void Image::Set_Rotate(const char* keyname, float Rotate)
{
	spriteList[keyname]->rotate = Rotate;
}

void Image::SetRenderState(IDirect3DDevice9* pD3DDevice, RENDERSTATE RenderState)
{
	switch (RenderState)
	{
	case RENDER_DEFAULT:
	{
		// 不透明オブジェクト
		pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);		//アルファテストの無効化
	}
	break;
	case RENDER_ALPHATEST:
	{
		// αテストによる透明領域の切り抜き
		pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);		//アルファテストの有効化
		pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x80);			//アルファ参照値
		pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);	//アルファテスト合格基準

	}
	break;
	}
}

float Image::Get_PosX(const char* keyname)
{
	return spriteList[keyname]->pos.x;
}

float Image::Get_PosY(const char* keyname)
{
	return spriteList[keyname]->pos.y;
}

int Image::Get_Width(const char* keyname)
{
	return spriteList[keyname]->width;
}

int Image::Get_Height(const char* keyname)
{
	return spriteList[keyname]->height;
}

float Image::Get_Rotate(const char* keyname)
{
	return spriteList[keyname]->rotate;
}

void Image::Move_Pos(const char* keyname, float x, float y)
{
	spriteList[keyname]->pos.x += x;
	spriteList[keyname]->pos.y += y;
}
void Image::Move_Rotate(const char* keyname, float Rotate)
{
	spriteList[keyname]->rotate += Rotate;
}

void Image::Set_Divide(const char* keyname, unsigned int DivU, unsigned int DivV)
{
	if (DivU <= 0 || DivV <= 0)
	{
		return;
	}

	spriteList[keyname]->divU = DivU;
	spriteList[keyname]->divV = DivV;
}

void Image::Set_UVNum(const char* keyname, unsigned int NumU, unsigned int NumV)
{
	if (NumU >= spriteList[keyname]->divU)
	{
		return;
	}
	if (NumV >= spriteList[keyname]->divV)
	{
		return;
	}

	spriteList[keyname]->numU = NumU;
	spriteList[keyname]->numV = NumV;
}

void Image::Draw(const char* keyname, IDirect3DDevice9* pDevice3D, bool isTurn)
{
	// 頂点情報セット
	Vertex _vtx[4] = {
		{ (float)spriteList[keyname]->width / 2,(float)-spriteList[keyname]->height / 2, 0.0f, 1.0f,(isTurn ? (float)spriteList[keyname]->numU / spriteList[keyname]->divU : (float)(spriteList[keyname]->numU + 1) / spriteList[keyname]->divU), (float)spriteList[keyname]->numV / spriteList[keyname]->divV},
		{ (float)spriteList[keyname]->width / 2,(float)spriteList[keyname]->height / 2, 0.0f, 1.0f,(isTurn ? (float)spriteList[keyname]->numU / spriteList[keyname]->divU : (float)(spriteList[keyname]->numU + 1) / spriteList[keyname]->divU), (float)(spriteList[keyname]->numV + 1) / spriteList[keyname]->divV},
		{ (float)-spriteList[keyname]->width / 2,(float)-spriteList[keyname]->height / 2, 0.0f, 1.0f,(isTurn ? (float)(spriteList[keyname]->numU + 1) / spriteList[keyname]->divU : (float)spriteList[keyname]->numU / spriteList[keyname]->divU), (float)spriteList[keyname]->numV / spriteList[keyname]->divV},
		{ (float)-spriteList[keyname]->width / 2,(float)spriteList[keyname]->height / 2, 0.0f, 1.0f,(isTurn ? (float)(spriteList[keyname]->numU + 1) / spriteList[keyname]->divU : (float)spriteList[keyname]->numU / spriteList[keyname]->divU), (float)(spriteList[keyname]->numV + 1) / spriteList[keyname]->divV}
	};

	for (int i = 0; i < 4; ++i) {
		float x = _vtx[i].x * cosf(spriteList[keyname]->rotate) - _vtx[i].y * sinf(spriteList[keyname]->rotate);
		float y = _vtx[i].x * sinf(spriteList[keyname]->rotate) + _vtx[i].y * cosf(spriteList[keyname]->rotate);
		_vtx[i].x = x + spriteList[keyname]->pos.x;
		_vtx[i].y = y + spriteList[keyname]->pos.y;
	}

	pDevice3D->SetTexture(0, textureList[keyname]);
	// 頂点構造体宣言セット
	pDevice3D->SetFVF(SPRITE_FVF);
	// スプライト描画
	pDevice3D->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, _vtx, sizeof(Vertex));
}


// 有向境界ボックス（２次元）
struct OBB
{
	D3DXVECTOR2	Pos;        // 位置
	D3DXVECTOR2	Dir[2];		// XY各座標軸の傾きを表す方向ベクトル
	float		Length[2];  // 各軸方向の長さの半分
};


// OBB作成
void CreateOBB(OBB* pOutOBB, const D3DXVECTOR2& Pos, const D3DXMATRIX& RotateMtx, const D3DXVECTOR2& Length)
{
	pOutOBB->Pos = Pos;
	pOutOBB->Length[0] = Length.x;
	pOutOBB->Length[1] = Length.y;
	pOutOBB->Dir[0] = D3DXVECTOR2(RotateMtx._11, RotateMtx._12);
	pOutOBB->Dir[1] = D3DXVECTOR2(RotateMtx._21, RotateMtx._22);
}


// 分離軸に投影された軸成分から投影線分長を算出
float LenSegOnSeparateAxis(D3DXVECTOR2* Sep, D3DXVECTOR2* e1, D3DXVECTOR2* e2)
{
	// 3つの内積の絶対値の和で投影線分長を計算
	// 分離軸Sepは標準化されていること
	float r1 = fabs(D3DXVec2Dot(Sep, e1));
	float r2 = fabs(D3DXVec2Dot(Sep, e2));
	return r1 + r2;
}

// OBB vs OBB
bool TestOBBOBB(const OBB& obb1, const OBB& obb2)
{
	// 各方向ベクトルの確保
	D3DXVECTOR2 NAe1 = obb1.Dir[0], Ae1 = NAe1 * obb1.Length[0];
	D3DXVECTOR2 NAe2 = obb1.Dir[1], Ae2 = NAe2 * obb1.Length[1];
	D3DXVECTOR2 NBe1 = obb2.Dir[0], Be1 = NBe1 * obb2.Length[0];
	D3DXVECTOR2 NBe2 = obb2.Dir[1], Be2 = NBe2 * obb2.Length[1];
	D3DXVECTOR2 Interval = obb1.Pos - obb2.Pos;

	// 分離軸 : Ae1
	float rA = D3DXVec2Length(&Ae1);
	float rB = LenSegOnSeparateAxis(&NAe1, &Be1, &Be2);
	float L = fabs(D3DXVec2Dot(&Interval, &NAe1));
	if (L > rA + rB)
		return false; // 衝突していない

	// 分離軸 : Ae2
	rA = D3DXVec2Length(&Ae2);
	rB = LenSegOnSeparateAxis(&NAe2, &Be1, &Be2);
	L = fabs(D3DXVec2Dot(&Interval, &NAe2));
	if (L > rA + rB)
		return false;

	// 分離軸 : Be1
	rA = LenSegOnSeparateAxis(&NBe1, &Ae1, &Ae2);
	rB = D3DXVec2Length(&Be1);
	L = fabs(D3DXVec2Dot(&Interval, &NBe1));
	if (L > rA + rB)
		return false;

	// 分離軸 : Be2
	rA = LenSegOnSeparateAxis(&NBe2, &Ae1, &Ae2);
	rB = D3DXVec2Length(&Be2);
	L = fabs(D3DXVec2Dot(&Interval, &NBe2));
	if (L > rA + rB)
		return false;

	// 分離平面が存在しないので「衝突している」
	return true;
}

bool IsHit(const char* keyname)
{
	Image* image = new Image();
	OBB obb1;
	OBB obb2;
	D3DXMATRIX rotMtx1;
	D3DXMATRIX rotMtx2;

	D3DXMatrixRotationZ(&rotMtx1, image->spriteList[keyname]->rotate);
	D3DXMatrixRotationZ(&rotMtx2, image->spriteList[keyname]->rotate);
	CreateOBB(&obb1, image->spriteList[keyname]->pos, rotMtx1, D3DXVECTOR2(image->spriteList[keyname]->width / 2.0f, image->spriteList[keyname]->height / 2.0f));
	CreateOBB(&obb2, image->spriteList[keyname]->pos, rotMtx2, D3DXVECTOR2(image->spriteList[keyname]->width / 2.0f, image->spriteList[keyname]->height / 2.0f));
	return TestOBBOBB(obb1, obb2);
}