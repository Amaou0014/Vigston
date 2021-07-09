#include "sprite.h"


// �R���X�g���N�^
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
// �f�X�g���N�^
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
		// �s�����I�u�W�F�N�g
		pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);		//�A���t�@�e�X�g�̖�����
	}
	break;
	case RENDER_ALPHATEST:
	{
		// ���e�X�g�ɂ�铧���̈�̐؂蔲��
		pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);		//�A���t�@�e�X�g�̗L����
		pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x80);			//�A���t�@�Q�ƒl
		pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);	//�A���t�@�e�X�g���i�

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
	// ���_���Z�b�g
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
	// �e�N�X�`���Z�b�g
	pDevice3D->SetTexture(0,pTexture);
	// ���_�\���̐錾�Z�b�g
	pDevice3D->SetFVF(SPRITE_FVF);
	// �X�v���C�g�`��
	pDevice3D->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,vtx,sizeof(Vertex));
}


// �L�����E�{�b�N�X�i�Q�����j
struct OBB 
{
   D3DXVECTOR2	Pos;        // �ʒu
   D3DXVECTOR2	Dir[2];		// XY�e���W���̌X����\�������x�N�g��
   float		Length[2];  // �e�������̒����̔���
};


// OBB�쐬
void CreateOBB(OBB* pOutOBB,const D3DXVECTOR2& Pos,const D3DXMATRIX& RotateMtx,const D3DXVECTOR2& Length)
{
	pOutOBB->Pos = Pos;
	pOutOBB->Length[0] = Length.x;
	pOutOBB->Length[1] = Length.y;
	pOutOBB->Dir[0] = D3DXVECTOR2(RotateMtx._11,RotateMtx._12);
	pOutOBB->Dir[1] = D3DXVECTOR2(RotateMtx._21,RotateMtx._22);
}


// �������ɓ��e���ꂽ���������瓊�e���������Z�o
float LenSegOnSeparateAxis( D3DXVECTOR2 *Sep, D3DXVECTOR2 *e1, D3DXVECTOR2 *e2 )
{
	// 3�̓��ς̐�Βl�̘a�œ��e���������v�Z
	// ������Sep�͕W��������Ă��邱��
	float r1 = fabs(D3DXVec2Dot( Sep, e1 ));
	float r2 = fabs(D3DXVec2Dot( Sep, e2 ));
	return r1 + r2;
}

// OBB vs OBB
bool TestOBBOBB(const OBB &obb1,const OBB &obb2)
{
	// �e�����x�N�g���̊m��
	// �iN***:�W���������x�N�g���j
	D3DXVECTOR2 NAe1 = obb1.Dir[0], Ae1 = NAe1 * obb1.Length[0];
	D3DXVECTOR2 NAe2 = obb1.Dir[1], Ae2 = NAe2 * obb1.Length[1];
	D3DXVECTOR2 NBe1 = obb2.Dir[0], Be1 = NBe1 * obb2.Length[0];
	D3DXVECTOR2 NBe2 = obb2.Dir[1], Be2 = NBe2 * obb2.Length[1];
	D3DXVECTOR2 Interval = obb1.Pos - obb2.Pos;

	// ������ : Ae1
	float rA = D3DXVec2Length( &Ae1 );
	float rB = LenSegOnSeparateAxis( &NAe1, &Be1, &Be2 );
	float L = fabs(D3DXVec2Dot( &Interval, &NAe1 ));
	if( L > rA + rB )
		return false; // �Փ˂��Ă��Ȃ�

	// ������ : Ae2
	rA = D3DXVec2Length( &Ae2 );
	rB = LenSegOnSeparateAxis( &NAe2, &Be1, &Be2);
	L = fabs(D3DXVec2Dot( &Interval, &NAe2 ));
	if( L > rA + rB )
		return false;

	// ������ : Be1
	rA = LenSegOnSeparateAxis( &NBe1, &Ae1, &Ae2);
	rB = D3DXVec2Length( &Be1 );
	L = fabs(D3DXVec2Dot( &Interval, &NBe1 ));
	if( L > rA + rB )
		return false;

	// ������ : Be2
	rA = LenSegOnSeparateAxis( &NBe2, &Ae1, &Ae2);
	rB = D3DXVec2Length( &Be2 );
	L = fabs(D3DXVec2Dot( &Interval, &NBe2 ));
	if( L > rA + rB )
		return false;

	// �������ʂ����݂��Ȃ��̂Łu�Փ˂��Ă���v
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