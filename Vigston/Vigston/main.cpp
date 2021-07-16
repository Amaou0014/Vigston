#include "vigston.h"

#include<string>

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Vigston vigston;

	Text text;

	vigston.Init();

	vigston.Load_Sound("SE1",(TCHAR*)_T("Resources/maou_retoro_1.wav"));
	vigston.Load_Image("Slime",(TCHAR*)_T("Resources/Slime.png"));
	vigston.Set_Image("Slime", 100, 100, 128, 128, 0);
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
				vigston.GetMouseState();

				

				if (vigston.GetKey(KEY_CODE_W))
				{
					vigston.Move_Image("Slime", 0, -10, 0);
				}
				if (vigston.GetKey(KEY_CODE_A))
				{
					vigston.Move_Image("Slime", -10, 0, 0);
				}
				if (vigston.GetKey(KEY_CODE_S))
				{
					vigston.Move_Image("Slime", 0, 10, 0);
				}
				if (vigston.GetKey(KEY_CODE_D))
				{
					vigston.Move_Image("Slime", 10, 0, 0);
				}

				if (vigston.PushKey(KEY_CODE_R))
				{
					vigston.Play_Sound("SE1", false);
					vigston.Move_Image("Slime", 0, 0, 5);
				}

				if (vigston.PushKey(KEY_CODE_T))
				{
					vigston.Move_Image("Slime", 0, 0, 5);
				}

				if (vigston.GetKey(KEY_CODE_LEFTMOUSE))
				{
					vigston.Draw_Font(300, 0, 0xffff0000, &text, _T("左クリック！！"));
				}

				if (vigston.GetKey(KEY_CODE_RIGHTMOUSE))
				{
					vigston.Draw_Font(300, 0, 0xffff0000, &text, _T("右クリック！！"));
				}

				if (vigston.GetKey(KEY_CODE_SENTERMOUSE))
				{
					vigston.Draw_Font(300, 0, 0xffff0000, &text, _T("ホイールクリック！！"));
				}


				// 描画処理
				vigston.Draw_Image("Slime");
				vigston.Draw_Font(0, 0, 0xffff0000,&text, _T("x = %.1f\ny = %.1f"), vigston.Get_Image_PosX("Slime"), vigston.Get_Image_PosY("Slime"));
				vigston.Draw_Font(200, 0, 0xffff0000, &text, _T("x = %d\ny = %d"), vigston.GetMouseX(), vigston.GetMouseY());
				// レンダリング終了
				vigston.End_Scene();
			}
			// 描画反映
			vigston.ScreenFlip();
		}
	}


	return 0;
}