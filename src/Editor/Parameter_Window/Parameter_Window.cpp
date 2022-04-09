#include"./Parameter_Window.h"

HWND* Parameter_Window::Parent_Handle;

void Parameter_Window::Set_ParentHandle(HWND* Handle) {
	Parent_Handle = Handle;
}


void Parameter_Window::Draw(HDC* hdc){}


/*���̊֐����Ə�肭�\���E��\����؂�ւ���Ȃ����߁A�I�[�o�[���C�h���Ĕh���N���X�ɏ���������*/
void Parameter_Window::Active() {
	std::list<HWND*>::iterator itr = Window_List.begin();
	while (itr != Window_List.end()) {
		if (!IsWindowEnabled((HWND)(*itr))) {
			EnableWindow((HWND)(*itr), true);
			ShowWindow((HWND)(*itr), SW_SHOW);
		}
		itr++;
	}
}

void Parameter_Window::Inactive() {
	std::list<HWND*>::iterator itr = Window_List.begin();
	while (itr != Window_List.end()) {
		if (IsWindowEnabled((HWND)(*itr))) {
			EnableWindow((HWND)(*itr), false);
			ShowWindow((HWND)(*itr), SW_HIDE);
		}
		itr++;
	}

}




