#include"./Editor.h"
#define EDITOR_WIDTH 400
#define EDITOR_HEIGHT 400

#define EDIT_HEIGTH 20

std::unique_ptr<Editor> Editor::SingleTon;
Parameter_Window* Editor::Chosen;


LRESULT CALLBACK EditProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
	
	
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		/*TODO:ちらつき防止用に何かする*/
		HDC hdc;
		PAINTSTRUCT ps;
		TEXTMETRIC tm;
		hdc = BeginPaint(hwnd, &ps);
		SetBkMode(hdc, TRANSPARENT);
		GetTextMetrics(hdc, &tm);
		Editor::Chosen->Draw(&hdc);
		EndPaint(hwnd, &ps);
	
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wp)) {
			case UPDATE_BUTTON:
				Editor::Get()->UpdateParameter();
				return 0;

			case HP_BUTTON:
				Editor::Get()->ChangeChosen(HP_BUTTON);
				break;
			case SBULLET_BUTTON:
				Editor::Get()->ChangeChosen(SBULLET_BUTTON);
				break;
			case MBULLET_BUTTON:
				Editor::Get()->ChangeChosen(MBULLET_BUTTON);
				break;
			case BBULLET_BUTTON:
				Editor::Get()->ChangeChosen(BBULLET_BUTTON);
				break;
			}
			return 0;

	case WM_KEYDOWN:				// キーが押された
		if (wp == VK_ESCAPE) {	// 押されたのはESCキーだ
			PostQuitMessage(0);		// アプリケーションを終了する
		}
		break;
	}
	return DefWindowProc(hwnd, msg, wp, lp);

}





Editor::Editor() {

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
	wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH); // ウィンドウ背景GRAY_BRUSH
	wc.lpszMenuName = NULL; // メニュー名
	wc.lpszClassName = TEXT("ParametersEditor");// ウィンドウクラス名

	// ウィンドウクラスを登録する
	if (RegisterClassEx(&wc) == 0) {  
		MessageBox(NULL,
			"EditorCreate", "失敗_Editor_WC", MB_OK);
	}
	
	DWORD dwStyle = WS_VISIBLE | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX;

	hWnd = CreateWindowEx(
		WS_EX_COMPOSITED,
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

	Parameter_Window::Set_ParentHandle(&hWnd);

	Update_Button = CreateWindow(
		(TCHAR*)"button", (TCHAR*) "更新",
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | WS_BORDER,
		200, 300, 100, 90, hWnd, (HMENU)UPDATE_BUTTON, this->hInstance, NULL);
	if (Update_Button == NULL) {
		MessageBox(NULL,
			"失敗_Update_Button", "EditorCreate", MB_OK);
	}
	
	Parameter* pram = Parameter::Get();
	
	HP = std::make_unique<HP_Window>(&hInstance, HP_BUTTON,pram->HP);
	Windows.push_back(HP.get());
	Chosen = HP.get();
	Chosen->Active();

	
	SBullet = std::make_unique<Bullet_Window>(&hInstance, SBULLET_BUTTON,(TCHAR*)"Bullet(小)",100,
												pram->SBulletSpeed,pram->SBulletPower,pram->SBulletReloadSpeed,pram->SBulletNum);
	Windows.push_back(SBullet.get());
	SBullet->Inactive();

	MBullet = std::make_unique<Bullet_Window>(&hInstance, MBULLET_BUTTON, (TCHAR*)"MBullet(中)", 200,
												pram->MBulletSpeed, pram->MBulletPower, pram->MBulletReloadSpeed, pram->MBulletNum);
	Windows.push_back(MBullet.get());
	MBullet->Inactive();

	BBullet = std::make_unique<Bullet_Window>(&hInstance, BBULLET_BUTTON, (TCHAR*)"BBullet(大)", 300,
												pram->BBulletSpeed, pram->BBulletPower, pram->BBulletReloadSpeed, pram->BBulletNum);
	Windows.push_back(BBullet.get());
	BBullet->Inactive();
}

void Editor::Update() {
	InvalidateRect(this->hWnd, NULL, true);
	UpdateWindow(this->hWnd);
	// ウィンドウが見えている時だけ描画するための処理
	WINDOWPLACEMENT wndpl;
	GetWindowPlacement(this->hWnd, &wndpl);	// ウインドウの状態を取得

}

void Editor::ChangeChosen(int Button_ID) {
	std::list<Parameter_Window*>::iterator itr = Windows.begin();
	while (itr != Windows.end()) {
		if((*itr)->ID == Button_ID){
			(*itr)->Active();
			Chosen = (*itr);
		}
		else {
			(*itr)->Inactive();
		}

		itr++;
	}
}

/*EditorProc関数(コールバック)の中からでもこのクラスを扱えるようにするためシングルトンパターンで実装する。*/
Editor* Editor::Get(){
	if (SingleTon.get() == nullptr) {
		SingleTon = std::make_unique<Editor>();
	}
	return SingleTon.get();
}

/*「更新」ボタンが押されるとこの関数を呼び出してパラメータを反映させる*/
void Editor::UpdateParameter() {
	Parameter* pram = Parameter::Get();
	HP->Update_Parameter(&pram->HP);
	SBullet->Update_Parameter(&pram->SBulletSpeed, &pram->SBulletPower, &pram->SBulletReloadSpeed, &pram->SBulletNum);
	MBullet->Update_Parameter(&pram->MBulletSpeed, &pram->MBulletPower, &pram->MBulletReloadSpeed, &pram->MBulletNum);
	BBullet->Update_Parameter(&pram->BBulletSpeed, &pram->BBulletPower, &pram->BBulletReloadSpeed, &pram->BBulletNum);
}