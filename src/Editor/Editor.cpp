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
					"EditorCreate", "���s_Editor_WC", MB_OK);
				return 0;
			}
			break;

	case WM_KEYDOWN:				// �L�[�������ꂽ
		if (wp == VK_ESCAPE) {	// �����ꂽ�̂�ESC�L�[��
			PostQuitMessage(0);		// �A�v���P�[�V�������I������
		}
		break;
	}
	return DefWindowProc(hwnd, msg, wp, lp);

}



Editor::Editor(WNDPROC proc,HINSTANCE hInstance) {

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
	wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH); // �E�B���h�E�w�i
	wc.lpszMenuName = NULL; // ���j���[��
	wc.lpszClassName = TEXT("ParametersEditor");// �E�B���h�E�N���X��

	// �E�B���h�E�N���X��o�^����
	if (RegisterClassEx(&wc) == 0) {  
		MessageBox(NULL,
			"EditorCreate", "���s_Editor_WC", MB_OK);
	}
	
	DWORD dwStyle = WS_VISIBLE | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX;

	hWnd = CreateWindow(
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

	button = CreateWindow(
		(TCHAR*)"button", (TCHAR*) "�X�V",
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
			"���s_EditorButton", "EditorCreate", MB_OK);
	}
	TextOut(GetDC(hWnd), 30, 30, (LPTSTR)"TestTTT", lstrlen("TestTTT"));

}

void Editor::Update(HWND hWnd) {
	// �E�B���h�E�������Ă��鎞�����`�悷�邽�߂̏���
	WINDOWPLACEMENT wndpl;
	GetWindowPlacement(this->hWnd, &wndpl);	// �E�C���h�E�̏�Ԃ��擾
}