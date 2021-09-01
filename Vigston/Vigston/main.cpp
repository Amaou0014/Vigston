#include "vigston.h"

#include<string>

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Vigston* vigston = new Vigston();

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
			// ƒŒƒ“ƒ_ƒŠƒ“ƒOŠJŽn
			if (vigston->Begine_Scene())
			{
				// ”wŒiFƒZƒbƒg
				vigston->Set_BackColor(0xff808080);
				// ”wŒiƒNƒŠƒA
				vigston->Clear_Screen();

				vigston->GetKeyState();
				vigston->GetMouseState();

				if (vigston->GetKey(KEY_CODE_W))
				{
					vigston->Move_Image("Slime", 0, -10, 0);
					vigston->Move_Image("AirShip", 0, -10, 0);
				}
				if (vigston->GetKey(KEY_CODE_A))
				{
					vigston->Move_Image("Slime", -10, 0, 0);
					vigston->Move_Image("AirShip", -10, 0, 0);
				}
				if (vigston->GetKey(KEY_CODE_S))
				{
					vigston->Move_Image("Slime", 0, 10, 0);
					vigston->Move_Image("AirShip", 0, 10, 0);
				}
				if (vigston->GetKey(KEY_CODE_D))
				{
					vigston->Move_Image("Slime", 10, 0, 0);
					vigston->Move_Image("AirShip", 10, 0, 0);
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

				// •`‰æˆ—
				vigston->Draw_Image("Slime");
				vigston->Draw_Image("AirShip");

				vigston->Draw_Font(0, 0, 0xffff0000, _T("x = %.1f\ny = %.1f"), vigston->Get_Image_PosX("Slime"), vigston->Get_Image_PosY("Slime"));
				vigston->Draw_Font(200, 0, 0xffff0000, _T("x = %d\ny = %d"), vigston->GetMouseX(), vigston->GetMouseY());

				// ƒŒƒ“ƒ_ƒŠƒ“ƒOI—¹
				vigston->End_Scene();
			}
			// •`‰æ”½‰f
			vigston->ScreenFlip();
		}
	}

	delete vigston;

	return 0;
}