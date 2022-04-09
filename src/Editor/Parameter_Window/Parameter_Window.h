#pragma once
#include <windows.h>
#include<list>
#include<stdlib.h>

/*値によってバグが発生*/
#define UPDATE_BUTTON 100
#define HP_BUTTON 200
#define SBULLET_BUTTON 300
#define MBULLET_BUTTON 350
#define BBULLET_BUTTON 400

#define ACTIVE true
#define INACTIVE false

#define CHOSE_BUTTON_SIZE 100



class Parameter_Window {
public:
	HWND Button;
	virtual void Inactive();
	virtual void Active();

	virtual void Draw(HDC* hdc);
	static void Set_ParentHandle(HWND* Handle);

	int ID;
protected:
	std::list<HWND*> Window_List;
	static HWND* Parent_Handle;
};

/*HPを編集するために必要なウィンドウ*/
class HP_Window:public Parameter_Window {
public:
	HP_Window(HINSTANCE* hInstance,int ID,float hp);
	void Draw(HDC* hdc) override;

	void Active() override;
	void Inactive() override;

	void Update_Parameter(float* hp);


private:
	HWND HP_Input;
};


/*幽霊(弾)のパラメータを編集するために必要なウィンドウ*/
class Bullet_Window:public Parameter_Window {
public:
	Bullet_Window(HINSTANCE* hInstance,int ID,TCHAR* ButtonName,int Button_x,float Speed,int Pow,int Reload,int Num);
	void Draw(HDC* hdc) override;
	void Active() override;
	void Inactive() override;

	void Update_Parameter(float* Speed,int* Power,int* Reload,int* Num);
private:
	HWND Speed_Input;
	HWND Power_Input;
	HWND Reload_Speed_Input;
	HWND Bullet_Number;
};