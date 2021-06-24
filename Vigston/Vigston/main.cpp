#include "vigston.h"


int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Vigston vigston;

	Texture tex_slime;
	Sprite sp_slime;

	vigston.Init(hInstance);

	vigston.Load_Texture((TCHAR*)_T("Resources/Slime.png"), &tex_slime);
	vigston.Set_Sprite(100, 100, 128, 128, 0, &sp_slime);

	while (!vigston.GameQuit())
	{
		if (vigston.ProcessMessage())
		{

		}
		else
		{
			// レンダリング開始
			if (vigston.Begine_Scene())
			{
				// 背景色セット
				vigston.Set_BackColor(0xff808080);
				// 背景クリア
				vigston.Clear_Screen();
				// 描画処理
				vigston.Draw(&tex_slime, &sp_slime);

				// レンダリング終了
				vigston.End_Scene();
			}
			// 描画反映
			vigston.direct3d.pDevice3D->Present(NULL, NULL, NULL, NULL);
		}
	}


	return 0;
}