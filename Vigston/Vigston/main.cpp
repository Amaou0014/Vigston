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
			// �����_�����O�J�n
			if (vigston.Begine_Scene())
			{
				// �w�i�F�Z�b�g
				vigston.Set_BackColor(0xff808080);
				// �w�i�N���A
				vigston.Clear_Screen();
				// �`�揈��
				vigston.Draw(&tex_slime, &sp_slime);

				// �����_�����O�I��
				vigston.End_Scene();
			}
			// �`�攽�f
			vigston.direct3d.pDevice3D->Present(NULL, NULL, NULL, NULL);
		}
	}


	return 0;
}