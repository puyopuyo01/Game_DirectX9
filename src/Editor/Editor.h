#pragma once
#include <iostream>
#include <windows.h>
#define IDC_EDIT1        100
#define IDC_LABEL1      110


class Editor {
public:
	Editor(WNDPROC proc,HINSTANCE hInstance);
	void Update(HWND hWnd);
private:
	WNDCLASSEX wc;
	HWND hWnd;
	HWND button;
	HWND edit;
	HINSTANCE hInstance;


};