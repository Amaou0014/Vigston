#include "vigston.h"


// メッセージ処理
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	switch (msg) {
		// ウィンドウが破棄されたとき
	case WM_DESTROY:
		PostQuitMessage(0);	// WM_QUITメッセージをメッセージキューに送る
		return 0;
	}
	// デフォルトのメッセージ処理
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

// WinMain関数（この関数が動く）
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Vigston vigston;

	vigston.WC_BASIC = _T("BASIC_WINDOW");
	// シンプルウィンドウクラス設定
	vigston.wcex = { sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,WndProc, 0,0,hInstance,
		(HICON)LoadImage(NULL,MAKEINTRESOURCE(IDI_APPLICATION),IMAGE_ICON,0,0,LR_DEFAULTSIZE | LR_SHARED),
		(HCURSOR)LoadImage(NULL,MAKEINTRESOURCE(IDC_ARROW),IMAGE_CURSOR,0,0,LR_DEFAULTSIZE | LR_SHARED),
		(HBRUSH)GetStockObject(WHITE_BRUSH), NULL, vigston.WC_BASIC , NULL };

	// シンプルウィンドウクラス作成
	if (!RegisterClassEx(&vigston.wcex))
		return false;

	// ウィンドウ幅、高さはディスプレイに依存する。普通は4:3
	vigston.WINDOW_WIDTH = 640;
	vigston.WINDOW_HEIGHT = 480;

	// ウィンドウの作成
	vigston.hWnd = CreateWindowEx(0, vigston.WC_BASIC,
		_T("VigstonApp"), WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, vigston.WINDOW_WIDTH, vigston.WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);

	vigston.Init(vigston.hWnd);

	vigston.Start();

	// メッセージループ
	MSG msg = {};
	while (msg.message != WM_QUIT) {
		// アプリケーションに送られてくるメッセージをメッセージキューから取得する
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			DispatchMessage(&msg);	// アプリケーションの各ウィンドウプロシージャにメッセージを転送する
		}
		// メッセージ処理をしていないとき
		else {
			// ここに各クラスのUpdateを書く
			vigston.Update();
		}
	}


	return 0;
}