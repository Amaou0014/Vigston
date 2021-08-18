#include "vigston.h"

#include<string>

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Vigston* vigston = new Vigston();

	Animation* anim = new Animation[12]
	{
		{0,0},// �R�}�P
		{1,0},// �R�}�Q
		{2,0},// �R�}�R
		{2,1},// �R�}�S
		{1,1},// �R�}�T
		{0,1},// �R�}�U
		{0,2},// �R�}�V
		{1,2},// �R�}�W
		{2,2},// �R�}�X
		{2,3},// �R�}�P�O
		{1,3},// �R�}�P�P
		{0,3},// �R�}�P�Q
	};

	vigston->Init();

	vigston->Load_Sound("SE1",(TCHAR*)_T("Resources/maou_retoro_1.wav"));
	vigston->Load_Image("Slime",(TCHAR*)_T("Resources/Slime.png"), 100, 100, 128, 128, 0);
	vigston->LoadDiv_Image("AirShip", (TCHAR*)_T("Resources/pipo-airship_1.png"), 200, 200, 64, 64, 0, 3, 4);
	vigston->Create_Font(32);

	while (!vigston->GameQuit())
	{
		if (vigston->ProcessMessage())
		{

		}
		else
		{
			// �����_�����O�J�n
			if (vigston->Begine_Scene())
			{
				// �w�i�F�Z�b�g
				vigston->Set_BackColor(0xff808080);
				// �w�i�N���A
				vigston->Clear_Screen();

				vigston->GetKeyState();
				vigston->GetMouseState();

				

				if (vigston->GetKey(KEY_CODE_W))
				{
					vigston->Move_Image("Slime", 0, -10, 0);
				}
				if (vigston->GetKey(KEY_CODE_A))
				{
					vigston->Move_Image("Slime", -10, 0, 0);
				}
				if (vigston->GetKey(KEY_CODE_S))
				{
					vigston->Move_Image("Slime", 0, 10, 0);
				}
				if (vigston->GetKey(KEY_CODE_D))
				{
					vigston->Move_Image("Slime", 10, 0, 0);
				}

				if (vigston->PushKey(KEY_CODE_R))
				{
					vigston->Play_Sound("SE1", false);
					vigston->Move_Image("Slime", 0, 0, 5);
				}

				if (vigston->PushKey(KEY_CODE_T))
				{
					vigston->Move_Image("Slime", 0, 0, 5);
				}

				if (vigston->GetKey(KEY_CODE_LEFTMOUSE))
				{
					vigston->Draw_Font(300, 0, 0xffff0000, _T("���N���b�N�I�I"));
				}

				if (vigston->GetKey(KEY_CODE_RIGHTMOUSE))
				{
					vigston->Draw_Font(300, 0, 0xffff0000, _T("�E�N���b�N�I�I"));
				}

				if (vigston->GetKey(KEY_CODE_SENTERMOUSE))
				{
					vigston->Draw_Font(300, 0, 0xffff0000, _T("�z�C�[���N���b�N�I�I"));
				}


				// �`�揈��
				vigston->Draw_Image("Slime");
				vigston->DrawDiv_Image("AirShip", anim, 10);
				vigston->Draw_Font(0, 0, 0xffff0000, _T("x = %.1f\ny = %.1f"), vigston->Get_Image_PosX("Slime"), vigston->Get_Image_PosY("Slime"));
				vigston->Draw_Font(200, 0, 0xffff0000, _T("x = %d\ny = %d"), vigston->GetMouseX(), vigston->GetMouseY());

				// �����_�����O�I��
				vigston->End_Scene();
			}
			// �`�攽�f
			vigston->ScreenFlip();
		}
	}

	delete vigston;


	return 0;
}