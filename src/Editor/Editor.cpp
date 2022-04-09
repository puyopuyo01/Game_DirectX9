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
		/*TODO:������h�~�p�ɉ�������*/
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

	case WM_KEYDOWN:				// �L�[�������ꂽ
		if (wp == VK_ESCAPE) {	// �����ꂽ�̂�ESC�L�[��
			PostQuitMessage(0);		// �A�v���P�[�V�������I������
		}
		break;
	}
	return DefWindowProc(hwnd, msg, wp, lp);

}





Editor::Editor() {

	// �E�B���h�E�N���X�̏���ݒ�
	wc.cbSize = sizeof(wc); // �\���̃T�C�Y
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_NOCLOSE; // �X�^�C��
	wc.lpfnWndProc = EditProc; // �E�B���h�E�v���V�[�W��
	wc.cbClsExtra = 0; // �g�����P
	wc.cbWndExtra = 0; // �g�����Q
	wc.hInstance = this->hInstance; // �C���X�^���X�n���h��
	wc.hIcon = NULL;
	wc.hIconSm = wc.hIcon; // �q�A�C�R��
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH); // �E�B���h�E�w�iGRAY_BRUSH
	wc.lpszMenuName = NULL; // ���j���[��
	wc.lpszClassName = TEXT("ParametersEditor");// �E�B���h�E�N���X��

	// �E�B���h�E�N���X��o�^����
	if (RegisterClassEx(&wc) == 0) {  
		MessageBox(NULL,
			"EditorCreate", "���s_Editor_WC", MB_OK);
	}
	
	DWORD dwStyle = WS_VISIBLE | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX;

	hWnd = CreateWindowEx(
		WS_EX_COMPOSITED,
		(TCHAR*)TEXT("ParametersEditor"), 			// �o�^����Ă���N���X��
		(TCHAR*)TEXT("Editor"), 			// �E�C���h�E��
		dwStyle,		// �E�C���h�E�X�^�C���i�|�b�v�A�b�v�E�C���h�E���쐬�j
		CW_USEDEFAULT, CW_USEDEFAULT, 					// �E�C���h�E�̉������̈ʒu,�E�C���h�E�̏c�����̈ʒu
		EDITOR_WIDTH, 		// �E�C���h�E�̕�
		EDITOR_HEIGHT,		// �E�C���h�E�̍���
		NULL,				// �e�E�C���h�E�̃n���h���i�ȗ��j
		NULL,				// ���j���[��q�E�C���h�E�̃n���h��
		this->hInstance, 			// �A�v���P�[�V�����C���X�^���X�̃n���h��
		NULL				// �E�C���h�E�̍쐬�f�[�^
	);

	if (hWnd == NULL) {
		MessageBox(NULL,
			"���s_EditorWindow", "EditorCreate", MB_OK);
	}

	// �E�B���h�E�T�C�Y���Đݒ肷��
	RECT rect;
	int ww, wh;
	int cw, ch;
	// �N���C�A���g�̈�̊O�̕����v�Z
	GetClientRect(hWnd, &rect);		// �N���C�A���g�����̃T�C�Y�̎擾
	cw = rect.right - rect.left;	// �N���C�A���g�̈�O�̉������v�Z
	ch = rect.bottom - rect.top;	// �N���C�A���g�̈�O�̏c�����v�Z

	// �E�C���h�E�S�̂̉����̕����v�Z
	GetWindowRect(hWnd, &rect);		// �E�C���h�E�S�̂̃T�C�Y�擾
	ww = rect.right - rect.left;	// �E�C���h�E�S�̂̕��̉������v�Z
	wh = rect.bottom - rect.top;	// �E�C���h�E�S�̂̕��̏c�����v�Z
	ww = ww - cw;					// �N���C�A���g�̈�ȊO�ɕK�v�ȕ�
	wh = wh - ch;					// �N���C�A���g�̈�ȊO�ɕK�v�ȍ���

	// �E�B���h�E�T�C�Y�̍Čv�Z
	ww = EDITOR_WIDTH + ww;			// �K�v�ȃE�C���h�E�̕�
	wh = EDITOR_HEIGHT + wh;		// �K�v�ȃE�C���h�E�̍���
	// �E�C���h�E�T�C�Y�̍Đݒ�
	SetWindowPos(hWnd, HWND_TOP, 0, 0, ww, wh, SW_SHOW);
	ShowWindow(hWnd, SW_SHOWNORMAL);
	ValidateRect(hWnd, 0);

	Parameter_Window::Set_ParentHandle(&hWnd);

	Update_Button = CreateWindow(
		(TCHAR*)"button", (TCHAR*) "�X�V",
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | WS_BORDER,
		200, 300, 100, 90, hWnd, (HMENU)UPDATE_BUTTON, this->hInstance, NULL);
	if (Update_Button == NULL) {
		MessageBox(NULL,
			"���s_Update_Button", "EditorCreate", MB_OK);
	}
	
	Parameter* pram = Parameter::Get();
	
	HP = std::make_unique<HP_Window>(&hInstance, HP_BUTTON,pram->HP);
	Windows.push_back(HP.get());
	Chosen = HP.get();
	Chosen->Active();

	
	SBullet = std::make_unique<Bullet_Window>(&hInstance, SBULLET_BUTTON,(TCHAR*)"Bullet(��)",100,
												pram->SBulletSpeed,pram->SBulletPower,pram->SBulletReloadSpeed,pram->SBulletNum);
	Windows.push_back(SBullet.get());
	SBullet->Inactive();

	MBullet = std::make_unique<Bullet_Window>(&hInstance, MBULLET_BUTTON, (TCHAR*)"MBullet(��)", 200,
												pram->MBulletSpeed, pram->MBulletPower, pram->MBulletReloadSpeed, pram->MBulletNum);
	Windows.push_back(MBullet.get());
	MBullet->Inactive();

	BBullet = std::make_unique<Bullet_Window>(&hInstance, BBULLET_BUTTON, (TCHAR*)"BBullet(��)", 300,
												pram->BBulletSpeed, pram->BBulletPower, pram->BBulletReloadSpeed, pram->BBulletNum);
	Windows.push_back(BBullet.get());
	BBullet->Inactive();
}

void Editor::Update() {
	InvalidateRect(this->hWnd, NULL, true);
	UpdateWindow(this->hWnd);
	// �E�B���h�E�������Ă��鎞�����`�悷�邽�߂̏���
	WINDOWPLACEMENT wndpl;
	GetWindowPlacement(this->hWnd, &wndpl);	// �E�C���h�E�̏�Ԃ��擾

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

/*EditorProc�֐�(�R�[���o�b�N)�̒�����ł����̃N���X��������悤�ɂ��邽�߃V���O���g���p�^�[���Ŏ�������B*/
Editor* Editor::Get(){
	if (SingleTon.get() == nullptr) {
		SingleTon = std::make_unique<Editor>();
	}
	return SingleTon.get();
}

/*�u�X�V�v�{�^�����������Ƃ��̊֐����Ăяo���ăp�����[�^�𔽉f������*/
void Editor::UpdateParameter() {
	Parameter* pram = Parameter::Get();
	HP->Update_Parameter(&pram->HP);
	SBullet->Update_Parameter(&pram->SBulletSpeed, &pram->SBulletPower, &pram->SBulletReloadSpeed, &pram->SBulletNum);
	MBullet->Update_Parameter(&pram->MBulletSpeed, &pram->MBulletPower, &pram->MBulletReloadSpeed, &pram->MBulletNum);
	BBullet->Update_Parameter(&pram->BBulletSpeed, &pram->BBulletPower, &pram->BBulletReloadSpeed, &pram->BBulletNum);
}