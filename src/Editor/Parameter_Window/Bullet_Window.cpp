#include"./Parameter_Window.h"



Bullet_Window::Bullet_Window(HINSTANCE* hInstance, int ID,TCHAR* ButtonName,int Button_x, float Speed, int Pow, int Reload, int Num) {
	this->ID = ID;
	Button = CreateWindow(
		(TCHAR*)"Button", (TCHAR*) ButtonName,
		WS_CHILD| WS_VISIBLE | BS_PUSHBUTTON | WS_BORDER,
		Button_x, 0, CHOSE_BUTTON_SIZE, 30, *Parent_Handle, (HMENU)ID,
		*hInstance, NULL);
	char S_buf[100];
	snprintf(S_buf, sizeof(S_buf), "%f", Speed);
	Speed_Input = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		(TCHAR*)"EDIT", (TCHAR*)S_buf,
		WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_NUMBER  | WS_BORDER,
		80, 60, 60, 30, *Parent_Handle, NULL,
		*hInstance, NULL);

	char P_buf[100];
	snprintf(P_buf, sizeof(P_buf), "%d", Pow);
	Power_Input = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		(TCHAR*)"EDIT", (TCHAR*)P_buf,
		WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_NUMBER | WS_BORDER,
		80, 90, 60, 30, *Parent_Handle, NULL,
		*hInstance, NULL);


	char R_buf[100];
	snprintf(R_buf, sizeof(R_buf), "%d", Reload);
	Reload_Speed_Input = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		(TCHAR*)"EDIT", (TCHAR*)R_buf,
		WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_NUMBER | WS_BORDER,
		80, 130, 60, 30, *Parent_Handle, NULL,
		*hInstance, NULL);


	char N_buf[100];
	snprintf(N_buf, sizeof(N_buf), "%d", Num);
	Bullet_Number = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		(TCHAR*)"EDIT", (TCHAR*)N_buf,
		WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_NUMBER | WS_BORDER,
		80, 160, 60, 30, *Parent_Handle, NULL,
		*hInstance, NULL);

	Window_List.push_back(&Speed_Input);
	Window_List.push_back(&Power_Input);
	Window_List.push_back(&Reload_Speed_Input);
	Window_List.push_back(&Bullet_Number);


}


void Bullet_Window::Draw(HDC* hdc) {
	LPSTR Speed = (LPSTR)"Speed";
	TextOut(*hdc, 30, 60,Speed, lstrlen(Speed));
	LPSTR Power = (LPSTR)"Power";
	TextOut(*hdc, 30, 90, Power, lstrlen(Power));
	LPSTR ReloadSpeed = (LPSTR)"Reload";
	TextOut(*hdc, 30, 130, ReloadSpeed, lstrlen(ReloadSpeed));
	LPSTR BulletNum = (LPSTR)"残弾数";
	TextOut(*hdc, 30, 160, BulletNum, lstrlen(BulletNum));
}

void Bullet_Window::Active() {
	EnableWindow(Speed_Input, true);
	ShowWindow(Speed_Input, SW_SHOW);

	EnableWindow(Power_Input, true);
	ShowWindow(Power_Input, SW_SHOW);

	EnableWindow(Reload_Speed_Input, true);
	ShowWindow(Reload_Speed_Input, SW_SHOW);

	EnableWindow(Bullet_Number, true);
	ShowWindow(Bullet_Number, SW_SHOW);
}

/*他のパラメータを編集するときにはこのウィンドウは非表示、非アクティブにする*/
void Bullet_Window::Inactive() {
	EnableWindow(Speed_Input, false);
	ShowWindow(Speed_Input, SW_HIDE);

	EnableWindow(Power_Input, false);
	ShowWindow(Power_Input, SW_HIDE);

	EnableWindow(Reload_Speed_Input, false);
	ShowWindow(Reload_Speed_Input, SW_HIDE);

	EnableWindow(Bullet_Number, false);
	ShowWindow(Bullet_Number, SW_HIDE);
}

void Bullet_Window::Update_Parameter(float* Speed, int* Power, int* Reload, int* Num) {
	char Speed_buf[100];
	Speed_buf[0] = '\0';

	GetWindowText(Speed_Input,Speed_buf,10);
	if (Speed_buf[0] == '\0') {
		MessageBox(NULL,
			"失敗_SpeedInput", "UpdateParameter", MB_OK);
	}

	*Speed = (float)atof(Speed_buf);

	char Power_buf[10];
	Power_buf[0] = '\0';

	GetWindowText(Power_Input, Power_buf, 3);
	if (Power_buf[0] == '\0') {
		MessageBox(NULL,
			"失敗_PowerInput", "UpdateParameter", MB_OK);
	}

	*Power = atoi(Power_buf);

	char Reload_buf[10];
	Reload_buf[0] = '\0';

	GetWindowText(Reload_Speed_Input, Reload_buf, 10);
	if (Reload_buf[0] == '\0') {
		MessageBox(NULL,
			"失敗_Reload_buft", "UpdateParameter", MB_OK);
	}

	*Reload = atoi(Reload_buf);

	char Bullet_buf[10];
	Bullet_buf[0] = '\0';

	GetWindowText(Bullet_Number, Bullet_buf, 10);
	if (Bullet_buf[0] == '\0') {
		MessageBox(NULL,
			"失敗_Bullet_buf", "UpdateParameter", MB_OK);
	}

	*Num = atoi(Bullet_buf);

}