#include "vigston.h"

#include<string>

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Vigston vigston;

	Texture tex_slime;
	Sprite sp_slime;

	Text text;

	vigston.Init(hInstance);

	vigston.Load_Texture((TCHAR*)_T("Resources/Slime.png"), &tex_slime);
	vigston.Set_Sprite(100, 100, 128, 128, 0, &sp_slime);
	vigston.Create_Font(32, &text);

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

				vigston.GetKeyState();

				

				if (vigston.GetKey(KEY_CODE_W))
				{
					vigston.Move_Sprite(0, -10, 0, &sp_slime);
				}
				if (vigston.GetKey(KEY_CODE_A))
				{
					vigston.Move_Sprite(-10, 0, 0, &sp_slime);
				}
				if (vigston.GetKey(KEY_CODE_S))
				{
					vigston.Move_Sprite(0, 10, 0, &sp_slime);
				}
				if (vigston.GetKey(KEY_CODE_D))
				{
					vigston.Move_Sprite(10, 0, 0, &sp_slime);
				}

				// 描画処理
				vigston.Draw_Image(&tex_slime, &sp_slime);
				vigston.Draw_Font(0, 0, 0xffff0000,&text, _T("x = %.1f\ny = %.1f"), sp_slime.pos.x, sp_slime.pos.y);
				// レンダリング終了
				vigston.End_Scene();
			}
			// 描画反映
			vigston.ScreenFlip();
		}
	}


	return 0;
}