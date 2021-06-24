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
			// ƒŒƒ“ƒ_ƒŠƒ“ƒOŠJŽn
			if (vigston.Begine_Scene())
			{
				// ”wŒiFƒZƒbƒg
				vigston.Set_BackColor(0xff808080);
				// ”wŒiƒNƒŠƒA
				vigston.Clear_Screen();
				// •`‰æˆ—
				vigston.Draw(&tex_slime, &sp_slime);

				// ƒŒƒ“ƒ_ƒŠƒ“ƒOI—¹
				vigston.End_Scene();
			}
			// •`‰æ”½‰f
			vigston.direct3d.pDevice3D->Present(NULL, NULL, NULL, NULL);
		}
	}


	return 0;
}