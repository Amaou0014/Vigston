#include "vigston.h"

#include<string>

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Vigston vigston;

	Texture tex_slime;
	Sprite sp_slime;

	Text text;

	vigston.Init(hInstance);

	vigston.Load_Sound("SE1",(TCHAR*)_T("Resources/maou_retoro_1.wav"));
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
				vigston.GetMouseState();

				

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

				if (vigston.PushKey(KEY_CODE_R))
				{
					vigston.Play_Sound("SE1", false);
					vigston.Move_Sprite(0, 0, 5, &sp_slime);
				}

				if (vigston.PushKey(KEY_CODE_T))
				{
					vigston.Move_Sprite(0, 0, 5, &sp_slime);
				}

				if (vigston.GetKey(KEY_CODE_LEFTMOUSE))
				{
					vigston.Draw_Font(300, 0, 0xffff0000, &text, _T("���N���b�N�I�I"));
				}

				if (vigston.GetKey(KEY_CODE_RIGHTMOUSE))
				{
					vigston.Draw_Font(300, 0, 0xffff0000, &text, _T("�E�N���b�N�I�I"));
				}

				if (vigston.GetKey(KEY_CODE_SENTERMOUSE))
				{
					vigston.Draw_Font(300, 0, 0xffff0000, &text, _T("�z�C�[���N���b�N�I�I"));
				}


				// �`�揈��
				vigston.Draw_Image(&tex_slime, &sp_slime);
				vigston.Draw_Font(0, 0, 0xffff0000,&text, _T("x = %.1f\ny = %.1f"), sp_slime.pos.x, sp_slime.pos.y);
				vigston.Draw_Font(200, 0, 0xffff0000, &text, _T("x = %d\ny = %d"), vigston.GetMouseX(), vigston.GetMouseY());
				// �����_�����O�I��
				vigston.End_Scene();
			}
			// �`�攽�f
			vigston.ScreenFlip();
		}
	}


	return 0;
}