#include "direct3d.h"

Direct3D::Direct3D(){
	pD3D9 = NULL;
	pDevice3D = NULL;
}
Direct3D::~Direct3D(){
	// DirectX�̃��������
	if(pDevice3D != NULL)
		pDevice3D->Release();
	if(pD3D9 != NULL)
		pD3D9->Release();
}

bool Direct3D::Create(HWND hWnd,int Width,int Height){
	
	// Direct3D9�I�u�W�F�N�g�̍쐬	
	pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);	
	// �f�B�X�v���C���擾
	D3DDISPLAYMODE Display;
	pD3D9->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &Display);

	D3DPRESENT_PARAMETERS	D3DParam = {			// �X���b�v�`�F�C���ݒ�
		Width,Height,Display.Format,1,D3DMULTISAMPLE_NONE,0,
		D3DSWAPEFFECT_DISCARD,hWnd,TRUE,TRUE,D3DFMT_D24S8,0,0,D3DPRESENT_INTERVAL_DEFAULT
	};			
	
	// HAL���[�h��3D�f�o�C�X�쐬
	if (FAILED(pD3D9->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL, D3DParam.hDeviceWindow,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &D3DParam, &pDevice3D)))
	if (FAILED(pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DParam.hDeviceWindow, 
		D3DCREATE_MIXED_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &D3DParam, &pDevice3D)))
	// REF���[�h��3D�f�o�C�X�쐬
	if (FAILED(pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, D3DParam.hDeviceWindow, 
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &D3DParam, &pDevice3D)))
	if (FAILED(pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, D3DParam.hDeviceWindow, 
		D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &D3DParam, &pDevice3D)))
	{
		// 3D�f�o�C�X�쐬���s(���̃O���t�B�b�N�{�[�h�ł�DirectX���g���Ȃ�)
		pD3D9->Release();
		return false;
	}

	return true;
}

// �����_�[�X�e�[�g�̕ύX
void SetRenderState(IDirect3DDevice9* pD3DDevice,RENDERSTATE RenderState)
{

	switch(RenderState)
	{
	case RENDER_DEFAULT:
		{
			// �s�����I�u�W�F�N�g
			pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);		//�A���t�@�e�X�g�̖�����
			pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);		//�A���t�@�u�����f�B���O�̖�����
		}
		break;
	case RENDER_ALPHATEST:
		{
			// ���e�X�g�ɂ�铧���̈�̐؂蔲��
			pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);			//�A���t�@�e�X�g�̗L����
			pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x80);					//�A���t�@�Q�ƒl
			pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);	//�A���t�@�e�X�g���i�
			
			pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);			//�A���t�@�u�����f�B���O�̖�����
		}
		break;
	case RENDER_HALFADD:
		{
			// �����Z����
			pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);			//�A���t�@�u�����f�B���O�̗L����
			pD3DDevice->SetRenderState(D3DRS_BLENDOP,  D3DBLENDOP_ADD );		//�u�����f�B���O�I�v�V�������Z
			pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);			//SRC�̐ݒ�
			pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);	//DEST�̐ݒ�

			pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			//�A���t�@�e�X�g�̖�����
		}
		break;
	case RENDER_ADD:
		{
			// �S���Z����
			pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);		//�A���t�@�u�����f�B���O�̗L����
			pD3DDevice->SetRenderState(D3DRS_BLENDOP,  D3DBLENDOP_ADD );	//�u�����f�B���O�I�v�V�������Z
			pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);		//SRC�̐ݒ�
			pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);		//DEST�̐ݒ�

			pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);		//�A���t�@�e�X�g�̖�����
		}
		break;
	}
}