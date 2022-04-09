#pragma once
#include <iostream>
#include <windows.h>
#include<memory.h>
#include"./Parameter_Window/Parameter_Window.h"
#include"Parameter/Parameter.h"
#define IDC_EDIT1        100
#define IDC_LABEL1      110



/*
キャラクターのパラメータを編集するウィンドウクラス
EditorProc関数(コールバック)の中からでもこのクラスを扱えるようにするためシングルトンパターンで実装する。
*/

/*パラメータ編集ウィンドウを制作して、ハードコーディングを避ける*/
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