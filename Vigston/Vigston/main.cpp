#include "vigston.h"

#include<string>

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Vigston* vigston = new Vigston();

	Animation* anim = new Animation[12]
	{
		{0,0},// コマ１
		{1,0},// コマ２
		{2,0},// コマ３
		{2,1},// コマ４
		{1,1},// コマ５
		{0,1},// コマ６
		{0,2},// コマ７
		{1,2},// コマ８
		{2,2},// コマ９
		{2,3},// コマ１０
		{1,3},// コマ１１
		{0,3},// コマ１２
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
			// レンダリング開始
			if (vigston->Begine_Scene())
			{
				// 背景色セット
				vigston->Set_BackColor(0xff808080);
				// 背景クリア
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
					vigston->Draw_Font(300, 0, 0xffff0000, _T("左クリック！！"));
				}

				if (vigston->GetKey(KEY_CODE_RIGHTMOUSE))
				{
					vigston->Draw_Font(300, 0, 0xffff0000, _T("右クリック！！"));
				}

				if (vigston->GetKey(KEY_CODE_SENTERMOUSE))
				{
					vigston->Draw_Font(300, 0, 0xffff0000, _T("ホイールクリック！！"));
				}


				// 描画処理
				vigston->Draw_Image("Slime");
				vigston->DrawDiv_Image("AirShip", anim, 10);
				vigston->Draw_Font(0, 0, 0xffff0000, _T("x = %.1f\ny = %.1f"), vigston->Get_Image_PosX("Slime"), vigston->Get_Image_PosY("Slime"));
				vigston->Draw_Font(200, 0, 0xffff0000, _T("x = %d\ny = %d"), vigston->GetMouseX(), vigston->GetMouseY());

				// レンダリング終了
				vigston->End_Scene();
			}
			// 描画反映
			vigston->ScreenFlip();
		}
	}

	delete vigston;


	return 0;
}