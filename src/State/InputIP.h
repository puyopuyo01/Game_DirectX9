#pragma once
#include "DXLib_Orig.h"
#include"Device/KeyBord/KeyBord.h"
#include"./Battle_State.h"
#include"./NetWork/EstCom.h"
#include"FPS/FPS.h"
#include<conio.h>

using namespace std;

class Game_State;
class Font;


class InputUI :public Field_Object {
public:
	InputUI(char *buf);
	void Draw() override;
private:
	Font* Text;
	char *buf;
};


/*通信したい相手のIPアドレスを入力するクラス*/
class InputIP :public Game_State {
public:
	InputIP();
	~InputIP();
	Game_State* Update() override;
private:
	char buf[14];
	unique_ptr<InputUI> inui;
	int index;

	bool AvalInp;
	int interval;
};
