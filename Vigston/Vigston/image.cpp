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
	// �e�N�X�`���ǂݍ��܂�Ă�����j��
	for (auto tex = textureList.begin(); tex != textureList.end(); tex++)
	{
		if (tex->second != nullptr)
		{
			tex->second->Release();
			tex->second = nullptr;
		}
	}

	textureList.clear();

	// �X�v���C�g�ǂݍ��܂�Ă�����j��
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
	// �摜�ǂݍ���
	if (FAILED(D3DXCreateTextureFromFile(pDevice3D, FileName, &textureList[keyname])))
	{
		return false;	// ���s
	}
	else
	{
		// ����
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
	// ���_���Z�b�g
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
	// ���_�\���̐錾�Z�b�g
	pDevice3D->SetFVF(SPRITE_FVF);
	// �X�v���C�g�`��
	pDevice3D->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, _vtx, sizeof(Vertex));
}


// �L�����E�{�b�N�X�i�Q�����j
struct OBB
{
	D3DXVECTOR2	Pos;        // �ʒu
	D3DXVECTOR2	Dir[2];		// XY�e���W���̌X����\�������x�N�g��
	float		Length[2];  // �e�������̒����̔���
};


// OBB�쐬
void CreateOBB(OBB* pOutOBB, const D3DXVECTOR2& Pos, const D3DXMATRIX& RotateMtx, const D3DXVECTOR2& Length)
{
	pOutOBB->Pos = Pos;
	pOutOBB->Length[0] = Length.x;
	pOutOBB->Length[1] = Length.y;
	pOutOBB->Dir[0] = D3DXVECTOR2(RotateMtx._11, RotateMtx._12);
	pOutOBB->Dir[1] = D3DXVECTOR2(RotateMtx._21, RotateMtx._22);
}


// �������ɓ��e���ꂽ���������瓊�e���������Z�o
float LenSegOnSeparateAxis(D3DXVECTOR2* Sep, D3DXVECTOR2* e1, D3DXVECTOR2* e2)
{
	// 3�̓��ς̐�Βl�̘a�œ��e���������v�Z
	// ������Sep�͕W��������Ă��邱��
	float r1 = fabs(D3DXVec2Dot(Sep, e1));
	float r2 = fabs(D3DXVec2Dot(Sep, e2));
	return r1 + r2;
}

// OBB vs OBB
bool TestOBBOBB(const OBB& obb1, const OBB& obb2)
{
	// �e�����x�N�g���̊m��
	D3DXVECTOR2 NAe1 = obb1.Dir[0], Ae1 = NAe1 * obb1.Length[0];
	D3DXVECTOR2 NAe2 = obb1.Dir[1], Ae2 = NAe2 * obb1.Length[1];
	D3DXVECTOR2 NBe1 = obb2.Dir[0], Be1 = NBe1 * obb2.Length[0];
	D3DXVECTOR2 NBe2 = obb2.Dir[1], Be2 = NBe2 * obb2.Length[1];
	D3DXVECTOR2 Interval = obb1.Pos - obb2.Pos;

	// ������ : Ae1
	float rA = D3DXVec2Length(&Ae1);
	float rB = LenSegOnSeparateAxis(&NAe1, &Be1, &Be2);
	float L = fabs(D3DXVec2Dot(&Interval, &NAe1));
	if (L > rA + rB)
		return false; // �Փ˂��Ă��Ȃ�

	// ������ : Ae2
	rA = D3DXVec2Length(&Ae2);
	rB = LenSegOnSeparateAxis(&NAe2, &Be1, &Be2);
	L = fabs(D3DXVec2Dot(&Interval, &NAe2));
	if (L > rA + rB)
		return false;

	// ������ : Be1
	rA = LenSegOnSeparateAxis(&NBe1, &Ae1, &Ae2);
	rB = D3DXVec2Length(&Be1);
	L = fabs(D3DXVec2Dot(&Interval, &NBe1));
	if (L > rA + rB)
		return false;

	// ������ : Be2
	rA = LenSegOnSeparateAxis(&NBe2, &Ae1, &Ae2);
	rB = D3DXVec2Length(&Be2);
	L = fabs(D3DXVec2Dot(&Interval, &NBe2));
	if (L > rA + rB)
		return false;

	// �������ʂ����݂��Ȃ��̂Łu�Փ˂��Ă���v
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