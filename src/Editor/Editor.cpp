#include"./Editor.h"
#define EDITOR_WIDTH 400
#define EDITOR_HEIGHT 400

#define BUTTON_ID 1

#define EDIT_HEIGTH 20


LRESULT CALLBACK EditProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wp)) {
			case WM_CREATE:
				MessageBox(NULL,
					"EditorCreate", "失敗_Editor_WC", MB_OK);
				return 0;
			}
			break;

	case WM_KEYDOWN:				// キーが押された
		if (wp == VK_ESCAPE) {	// 押されたのはESCキーだ
			PostQuitMessage(0);		// アプリケーションを終了する
		}
		break;
	}
	return DefWindowProc(hwnd, msg, wp, lp);

}



Editor::Editor(WNDPROC proc,HINSTANCE hInstance) {

	// ウィンドウクラスの情報を設定
	wc.cbSize = sizeof(wc); // 構造体サイズ
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_NOCLOSE; // スタイル
	wc.lpfnWndProc = EditProc; // ウィンドウプロシージャ
	wc.cbClsExtra = 0; // 拡張情報１
	wc.cbWndExtra = 0; // 拡張情報２
	wc.hInstance = this->hInstance; // インスタンスハンドル
	wc.hIcon = NULL;
	wc.hIconSm = wc.hIcon; // 子アイコン
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH); // ウィンドウ背景
	wc.lpszMenuName = NULL; // メニュー名
	wc.lpszClassName = TEXT("ParametersEditor");// ウィンドウクラス名

	// ウィンドウクラスを登録する
	if (RegisterClassEx(&wc) == 0) {  
		MessageBox(NULL,
			"EditorCreate", "失敗_Editor_WC", MB_OK);
	}
	
	DWORD dwStyle = WS_VISIBLE | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX;

	hWnd = CreateWindow(
		(TCHAR*)TEXT("ParametersEditor"), 			// 登録されているクラス名
		(TCHAR*)TEXT("Editor"), 			// ウインドウ名
		dwStyle,		// ウインドウスタイル（ポップアップウインドウを作成）
		CW_USEDEFAULT, CW_USEDEFAULT, 					// ウインドウの横方向の位置,ウインドウの縦方向の位置
		EDITOR_WIDTH, 		// ウインドウの幅
		EDITOR_HEIGHT,		// ウインドウの高さ
		NULL,				// 親ウインドウのハンドル（省略）
		NULL,				// メニューや子ウインドウのハンドル
		this->hInstance, 			// アプリケーションインスタンスのハンドル
		NULL				// ウインドウの作成データ
	);

	if (hWnd == NULL) {
		MessageBox(NULL,
			"失敗_EditorWindow", "EditorCreate", MB_OK);
	}

	// ウィンドウサイズを再設定する
	RECT rect;
	int ww, wh;
	int cw, ch;
	// クライアント領域の外の幅を計算
	GetClientRect(hWnd, &rect);		// クライアント部分のサイズの取得
	cw = rect.right - rect.left;	// クライアント領域外の横幅を計算
	ch = rect.bottom - rect.top;	// クライアント領域外の縦幅を計算

	// ウインドウ全体の横幅の幅を計算
	GetWindowRect(hWnd, &rect);		// ウインドウ全体のサイズ取得
	ww = rect.right - rect.left;	// ウインドウ全体の幅の横幅を計算
	wh = rect.bottom - rect.top;	// ウインドウ全体の幅の縦幅を計算
	ww = ww - cw;					// クライアント領域以外に必要な幅
	wh = wh - ch;					// クライアント領域以外に必要な高さ

	// ウィンドウサイズの再計算
	ww = EDITOR_WIDTH + ww;			// 必要なウインドウの幅
	wh = EDITOR_HEIGHT + wh;		// 必要なウインドウの高さ
	// ウインドウサイズの再設定
	SetWindowPos(hWnd, HWND_TOP, 0, 0, ww, wh, SW_SHOW);
	ShowWindow(hWnd, SW_SHOWNORMAL);
	ValidateRect(hWnd, 0);

	button = CreateWindow(
		(TCHAR*)"button", (TCHAR*) "更新",
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | WS_BORDER,
		250, 300, 30, 60, hWnd, (HMENU)BUTTON_ID, this->hInstance, NULL);
		

	edit = CreateWindow(
				(TCHAR*)"EDIT", (TCHAR*)"1122",
				WS_CHILD|WS_VISIBLE|ES_LEFT|ES_NUMBER| ES_MULTILINE | WS_BORDER,
				0, 0, 100, 30, hWnd, (HMENU)2,
				this->hInstance, NULL);

	edit = CreateWindow(
		(TCHAR*)"EDIT", NULL,
		WS_CHILD | WS_VISIBLE | ES_LEFT | ES_NUMBER,
		100, 60, 100, 60, hWnd, (HMENU)2,
		this->hInstance, NULL);
	ShowWindow(edit, SW_HIDE);
	if (edit == NULL) {
		MessageBox(NULL,
			"失敗_EditorButton", "EditorCreate", MB_OK);
	}
	TextOut(GetDC(hWnd), 30, 30, (LPTSTR)"TestTTT", lstrlen("TestTTT"));

}

void Editor::Update(HWND hWnd) {
	// ウィンドウが見えている時だけ描画するための処理
	WINDOWPLACEMENT wndpl;
	GetWindowPlacement(this->hWnd, &wndpl);	// ウインドウの状態を取得
}