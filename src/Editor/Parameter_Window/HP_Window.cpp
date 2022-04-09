#include"./Parameter_Window.h"

HP_Window::HP_Window(HINSTANCE* hInstance, int ID,float hp) {
	this->ID = ID;

	char hp_buf[100];
	snprintf(hp_buf, sizeof(hp_buf), "%f", hp);
	Button = CreateWindow(
		(TCHAR*)"Button", (TCHAR*) "HP",
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | WS_BORDER,
		0, 0,CHOSE_BUTTON_SIZE, 30, *Parent_Handle, (HMENU)HP_BUTTON,
		*hInstance, NULL);

	HP_Input = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		(TCHAR*)"EDIT", (TCHAR*)hp_buf,
		WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_NUMBER | ES_MULTILINE | WS_BORDER,
		50, 60, 100, 30, *Parent_Handle, (HMENU)2,
		*hInstance, NULL);
	this->Window_List.push_back(&HP_Input);
}

void HP_Window::Draw(HDC* hdc) {
	LPSTR hp = (LPSTR)"HP";
	TextOut(*hdc, 30, 60, hp, lstrlen(hp));
	SetWindowText(*Parent_Handle, hp);
}

void HP_Window::Active() {
	EnableWindow(HP_Input, true);
	ShowWindow(HP_Input, SW_SHOW);
}

/*他のパラメータを編集するときにはこのウィンドウは非表示、非アクティブにする*/
void HP_Window::Inactive() {
	EnableWindow(HP_Input, false);
	ShowWindow(HP_Input, SW_HIDE);
}


void HP_Window::Update_Parameter(float* hp) {
	char hp_buf[100];
	hp_buf[0] = '\0';

	GetWindowText(HP_Input, hp_buf, 10);
	if (hp_buf[0] == '\0') {
		MessageBox(NULL,
			"失敗_HPInput", "UpdateParameter", MB_OK);
	}

	*hp= (float)atof(hp_buf);
}