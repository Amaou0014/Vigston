#pragma once

#define D3D_DEBUG_INFO	// Direct3D�f�o�b�N�t���O

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3dxof.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")
#include <comdef.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <mmsystem.h>


// Direct3D�N���X
class Direct3D
{
public:
	IDirect3D9*				pD3D9;			// Direct3D�f�o�C�X�����p�I�u�W�F�N�g
	IDirect3DDevice9*		pDevice3D;		// Direct3D�̃f�o�C�X

	Direct3D();
	~Direct3D();

	// �f�o�C�X�쐬
	bool Create(HWND hWnd,int Width,int Height);
};

// �����_�[�X�e�[�g�̐ݒ�
enum RENDERSTATE
{
	RENDER_DEFAULT,		// �f�t�H���g(�s����)
	RENDER_ALPHATEST,	// ���e�X�g
	RENDER_HALFADD,		// �����Z����
	RENDER_ADD			// ���Z����
};

// �����_�[�X�e�[�g�̕ύX
void SetRenderState(IDirect3DDevice9* pD3DDevice,RENDERSTATE RenderState);
