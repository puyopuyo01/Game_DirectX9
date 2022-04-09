#pragma once
#include <iostream>
#include <windows.h>
#include<memory.h>
#include"./Parameter_Window/Parameter_Window.h"
#include"Parameter/Parameter.h"
#define IDC_EDIT1        100
#define IDC_LABEL1      110



/*
�L�����N�^�[�̃p�����[�^��ҏW����E�B���h�E�N���X
EditorProc�֐�(�R�[���o�b�N)�̒�����ł����̃N���X��������悤�ɂ��邽�߃V���O���g���p�^�[���Ŏ�������B
*/

/*�p�����[�^�ҏW�E�B���h�E�𐧍삵�āA�n�[�h�R�[�f�B���O�������*/
class Editor {
public:
	Editor();
	void Update();

	void ChangeChosen(int Button_ID);



	static Editor* Get();
	static Parameter_Window* Chosen;


	void UpdateParameter();
private:
	WNDCLASSEX wc;
	HWND hWnd;
	
	HWND Update_Button;
	HINSTANCE hInstance;

	std::unique_ptr<HP_Window> HP;
	std::unique_ptr<Bullet_Window> SBullet;
	std::unique_ptr<Bullet_Window> MBullet;
	std::unique_ptr<Bullet_Window> BBullet;

	static std::unique_ptr<Editor> SingleTon;
	std::list<Parameter_Window*> Windows;


};