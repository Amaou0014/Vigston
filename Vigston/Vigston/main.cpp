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
			// �����_�����O�J�n
			if (vigston.Begine_Scene())
			{
				// �w�i�F�Z�b�g
				vigston.Set_BackColor(0xff808080);
				// �w�i�N���A
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

				// �`�揈��
				vigston.Draw_Image(&tex_slime, &sp_slime);
				vigston.Draw_Font(0, 0, 0xffff0000,&text, _T("x = %.1f\ny = %.1f"), sp_slime.pos.x, sp_slime.pos.y);
				// �����_�����O�I��
				vigston.End_Scene();
			}
			// �`�攽�f
			vigston.ScreenFlip();
		}
	}


	return 0;
}