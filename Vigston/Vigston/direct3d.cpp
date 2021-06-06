#include "direct3d.h"

Direct3D::Direct3D(){
	pD3D9 = NULL;
	pDevice3D = NULL;
}
Direct3D::~Direct3D(){
	// DirectXのメモリ解放
	if(pDevice3D != NULL)
		pDevice3D->Release();
	if(pD3D9 != NULL)
		pD3D9->Release();
}

bool Direct3D::Create(HWND hWnd,int Width,int Height){
	
	// Direct3D9オブジェクトの作成	
	pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);	
	// ディスプレイ情報取得
	D3DDISPLAYMODE Display;
	pD3D9->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &Display);

	D3DPRESENT_PARAMETERS	D3DParam = {			// スワップチェイン設定
		Width,Height,Display.Format,1,D3DMULTISAMPLE_NONE,0,
		D3DSWAPEFFECT_DISCARD,hWnd,TRUE,TRUE,D3DFMT_D24S8,0,0,D3DPRESENT_INTERVAL_DEFAULT
	};			
	
	// HALモードで3Dデバイス作成
	if (FAILED(pD3D9->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL, D3DParam.hDeviceWindow,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &D3DParam, &pDevice3D)))
	if (FAILED(pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DParam.hDeviceWindow, 
		D3DCREATE_MIXED_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &D3DParam, &pDevice3D)))
	// REFモードで3Dデバイス作成
	if (FAILED(pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, D3DParam.hDeviceWindow, 
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &D3DParam, &pDevice3D)))
	if (FAILED(pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, D3DParam.hDeviceWindow, 
		D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &D3DParam, &pDevice3D)))
	{
		// 3Dデバイス作成失敗(このグラフィックボードではDirectXが使えない)
		pD3D9->Release();
		return false;
	}

	return true;
}

// レンダーステートの変更
void SetRenderState(IDirect3DDevice9* pD3DDevice,RENDERSTATE RenderState)
{

	switch(RenderState)
	{
	case RENDER_DEFAULT:
		{
			// 不透明オブジェクト
			pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);		//アルファテストの無効化
			pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);		//アルファブレンディングの無効化
		}
		break;
	case RENDER_ALPHATEST:
		{
			// αテストによる透明領域の切り抜き
			pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);			//アルファテストの有効化
			pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x80);					//アルファ参照値
			pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);	//アルファテスト合格基準
			
			pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);			//アルファブレンディングの無効化
		}
		break;
	case RENDER_HALFADD:
		{
			// 半加算合成
			pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);			//アルファブレンディングの有効化
			pD3DDevice->SetRenderState(D3DRS_BLENDOP,  D3DBLENDOP_ADD );		//ブレンディングオプション加算
			pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);			//SRCの設定
			pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);	//DESTの設定

			pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			//アルファテストの無効化
		}
		break;
	case RENDER_ADD:
		{
			// 全加算合成
			pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);		//アルファブレンディングの有効化
			pD3DDevice->SetRenderState(D3DRS_BLENDOP,  D3DBLENDOP_ADD );	//ブレンディングオプション加算
			pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);		//SRCの設定
			pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);		//DESTの設定

			pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);		//アルファテストの無効化
		}
		break;
	}
}