#include "sprite.h"


// コンストラクタ
Sprite::Sprite()
{
	pos.x = 0.0f;
	pos.y = 0.0f;
	width = 0;
	height = 0;
	divU = 1;
	divV = 1;
	numU = 0;
	numV = 0;
	rotate = 0.0f;
}
// デストラクタ
Sprite::~Sprite(){}

void Sprite::Set_Pos(float x,float y)
{
	pos.x = x;
	pos.y = y;
}
void Sprite::Set_Width(int Width,int Height)
{
	width = Width;
	height = Height;
}

void Sprite::Set_Rotate(float Rotate)
{
	rotate = Rotate;
}

void Sprite::SetRenderState(IDirect3DDevice9* pD3DDevice, RENDERSTATE RenderState)
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

float Sprite::Get_PosX()
{
	return pos.x;
}

float Sprite::Get_PosY()
{
	return pos.y;
}

int Sprite::Get_Width()
{
	return width;
}

int Sprite::Get_Height()
{
	return height;
}

float Sprite::Get_Rotate()
{
	return rotate;
}

void Sprite::Move_Pos(float x,float y)
{
	pos.x += x;
	pos.y += y;
}
void Sprite::Move_Rotate(float Rotate)
{
	rotate += Rotate;
}

void Sprite::Set_Divide(unsigned int DivU,unsigned int DivV)
{
	if(DivU <= 0 || DivV <= 0)
		return;

	divU = DivU;
	divV = DivV;
}

void Sprite::Set_UVNum(unsigned int NumU,unsigned int NumV)
{
	if(NumU >= divU)
		return;
	if(NumV >= divV)
		return;

	numU = NumU;
	numV = NumV;
}

void Sprite::Draw(IDirect3DDevice9* pDevice3D,IDirect3DTexture9* pTexture,bool isTurn)
{
	// 頂点情報セット
	Vertex vtx[4]={
		{ (float) width/2,(float)-height/2, 0.0f, 1.0f,(isTurn ? (float)numU/divU : (float)(numU + 1)/divU), (float)numV/divV},
		{ (float) width/2,(float) height/2, 0.0f, 1.0f,(isTurn ? (float)numU/divU : (float)(numU + 1)/divU), (float)(numV + 1)/divV}, 
		{ (float)-width/2,(float)-height/2, 0.0f, 1.0f,(isTurn ? (float)(numU + 1)/divU : (float)numU/divU), (float)numV/divV}, 
		{ (float)-width/2,(float) height/2, 0.0f, 1.0f,(isTurn ? (float)(numU + 1)/divU : (float)numU/divU), (float)(numV + 1)/divV} 
	};

	for(int i = 0;i < 4;++i){
		float x = vtx[i].x * cosf(rotate) - vtx[i].y * sinf(rotate);
		float y = vtx[i].x * sinf(rotate) + vtx[i].y * cosf(rotate);
		vtx[i].x = x + pos.x;
		vtx[i].y = y + pos.y;
	}
	// テクスチャセット
	pDevice3D->SetTexture(0,pTexture);
	// 頂点構造体宣言セット
	pDevice3D->SetFVF(SPRITE_FVF);
	// スプライト描画
	pDevice3D->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,vtx,sizeof(Vertex));
}


// 有向境界ボックス（２次元）
struct OBB 
{
   D3DXVECTOR2	Pos;        // 位置
   D3DXVECTOR2	Dir[2];		// XY各座標軸の傾きを表す方向ベクトル
   float		Length[2];  // 各軸方向の長さの半分
};


// OBB作成
void CreateOBB(OBB* pOutOBB,const D3DXVECTOR2& Pos,const D3DXMATRIX& RotateMtx,const D3DXVECTOR2& Length)
{
	pOutOBB->Pos = Pos;
	pOutOBB->Length[0] = Length.x;
	pOutOBB->Length[1] = Length.y;
	pOutOBB->Dir[0] = D3DXVECTOR2(RotateMtx._11,RotateMtx._12);
	pOutOBB->Dir[1] = D3DXVECTOR2(RotateMtx._21,RotateMtx._22);
}


// 分離軸に投影された軸成分から投影線分長を算出
float LenSegOnSeparateAxis( D3DXVECTOR2 *Sep, D3DXVECTOR2 *e1, D3DXVECTOR2 *e2 )
{
	// 3つの内積の絶対値の和で投影線分長を計算
	// 分離軸Sepは標準化されていること
	float r1 = fabs(D3DXVec2Dot( Sep, e1 ));
	float r2 = fabs(D3DXVec2Dot( Sep, e2 ));
	return r1 + r2;
}

// OBB vs OBB
bool TestOBBOBB(const OBB &obb1,const OBB &obb2)
{
	// 各方向ベクトルの確保
	// （N***:標準化方向ベクトル）
	D3DXVECTOR2 NAe1 = obb1.Dir[0], Ae1 = NAe1 * obb1.Length[0];
	D3DXVECTOR2 NAe2 = obb1.Dir[1], Ae2 = NAe2 * obb1.Length[1];
	D3DXVECTOR2 NBe1 = obb2.Dir[0], Be1 = NBe1 * obb2.Length[0];
	D3DXVECTOR2 NBe2 = obb2.Dir[1], Be2 = NBe2 * obb2.Length[1];
	D3DXVECTOR2 Interval = obb1.Pos - obb2.Pos;

	// 分離軸 : Ae1
	float rA = D3DXVec2Length( &Ae1 );
	float rB = LenSegOnSeparateAxis( &NAe1, &Be1, &Be2 );
	float L = fabs(D3DXVec2Dot( &Interval, &NAe1 ));
	if( L > rA + rB )
		return false; // 衝突していない

	// 分離軸 : Ae2
	rA = D3DXVec2Length( &Ae2 );
	rB = LenSegOnSeparateAxis( &NAe2, &Be1, &Be2);
	L = fabs(D3DXVec2Dot( &Interval, &NAe2 ));
	if( L > rA + rB )
		return false;

	// 分離軸 : Be1
	rA = LenSegOnSeparateAxis( &NBe1, &Ae1, &Ae2);
	rB = D3DXVec2Length( &Be1 );
	L = fabs(D3DXVec2Dot( &Interval, &NBe1 ));
	if( L > rA + rB )
		return false;

	// 分離軸 : Be2
	rA = LenSegOnSeparateAxis( &NBe2, &Ae1, &Ae2);
	rB = D3DXVec2Length( &Be2 );
	L = fabs(D3DXVec2Dot( &Interval, &NBe2 ));
	if( L > rA + rB )
		return false;

	// 分離平面が存在しないので「衝突している」
	return true;
}

bool IsHit(const Sprite& sprite1,const Sprite& sprite2)
{
	OBB obb1;
	OBB obb2;
	D3DXMATRIX rotMtx1;
	D3DXMATRIX rotMtx2;

	D3DXMatrixRotationZ(&rotMtx1,sprite1.rotate);
	D3DXMatrixRotationZ(&rotMtx2,sprite2.rotate);
	CreateOBB(&obb1,sprite1.pos,rotMtx1,D3DXVECTOR2(sprite1.width/2.0f,sprite1.height/2.0f));
	CreateOBB(&obb2,sprite2.pos,rotMtx2,D3DXVECTOR2(sprite2.width/2.0f,sprite2.height/2.0f));
	return TestOBBOBB(obb1,obb2);
}